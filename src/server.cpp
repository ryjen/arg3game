#include "area.h"
#include "server.h"
#include "location.h"
#include "exit.h"
#include "exception.h"
#include <thread>
#include <arg3/log.h>
#include <arg3format/format.h>

using namespace arg3::net;

namespace arg3
{
    namespace game
    {
        typedef struct {
            std::shared_ptr<websocket_connection> conn;
            lws_context *context;
        } websocket_user_info;

        static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
        {
            return 0;
        }

        int websocket_server_callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
        {
            websocket_user_info *info = (websocket_user_info *)user;

            switch (reason) {
                case LWS_CALLBACK_ESTABLISHED:  // just log message that someone is connecting
                {
                    info->conn = std::make_shared<websocket_connection>(wsi);
                    websocket_server *server = (websocket_server *)lws_context_user(info->context);
                    info->conn->set_world(server->world());
                    server->add_websocket(info->conn);
                    info->conn->show_welcome();
                    lws_callback_on_writable(wsi);
                    break;
                }
                case LWS_CALLBACK_RECEIVE:  // the funny part
                {
                    info->conn->buffered_writer::writeln();
                    info->conn->process_input((char *)in);
                    lws_callback_on_writable(wsi);
                    break;
                }
                case LWS_CALLBACK_SERVER_WRITEABLE: {
                    info->conn->show_prompt();
                    info->conn->write_from_buffer();
                    break;
                }
                default:
                    break;
            }


            return 0;
        }

        static struct lws_protocols protocols[] = {
            /* first protocol must always be HTTP handler */
            {
                "http-only",    // name
                callback_http,  // callback
                0               // per_session_data_size
            },
            {"arg3-mud-protocol",         // protocol name - very important!
             &websocket_server_callback,  // callback
             sizeof(websocket_user_info)

            },
            {
                NULL, NULL, 0 /* End of list */
            }};

        bool server::can_poll(struct timeval *last_time, int pollFrequency)
        {
            struct timeval now_time;
            long secDelta;
            long usecDelta;

            if (last_time == NULL) {
                return true;
            }

            gettimeofday(&now_time, NULL);

            usecDelta = ((int)last_time->tv_usec) - ((int)now_time.tv_usec) + 1000000 / pollFrequency;
            secDelta = ((int)last_time->tv_sec) - ((int)now_time.tv_sec);

            while (usecDelta < 0) {
                usecDelta += 1000000;
                secDelta -= 1;
            }

            while (usecDelta >= 1000000) {
                usecDelta -= 1000000;
                secDelta += 1;
            }

            // check if server should stall for a moment based on poll frequency
            if (secDelta > 0 || (secDelta == 0 && usecDelta > 0)) {
                return false;
            }

            gettimeofday(last_time, NULL);

            return true;
        }

        void websocket_server::add_websocket(shared_ptr<websocket_connection> conn)
        {
            websockets_.push_back(conn);
        }

        void websocket_server::remove_websocket(shared_ptr<websocket_connection> conn)
        {
            websockets_.erase(find(websockets_.begin(), websockets_.end(), conn));
        }

        vector<shared_ptr<websocket_connection>> &websocket_server::websockets()
        {
            return websockets_;
        }

        bool websocket_server::start()
        {
            struct lws_context_creation_info info;

            memset(&info, 0, sizeof info);
            info.port = world()->websocket_port();
            info.iface = NULL;
            info.protocols = protocols;
            info.extensions = lws_get_internal_extensions();
            info.ssl_cert_filepath = NULL;
            info.ssl_private_key_filepath = NULL;
            info.gid = -1;
            info.uid = -1;
            info.options = 0;
            info.user = this;

            context_ = lws_create_context(&info);

            return context_ != NULL;
        }

        void websocket_server::poll()
        {
            lws_service(context_, 1);
        }

        int websocket_server::port() const
        {
            return world()->websocket_port();
        }

        server::server(world_ptr world) : world_(world), db_(make_shared<database>(world->db_name()))
        {
        }

        websocket_server::websocket_server(world_ptr world) : server(world), context_(NULL)
        {
        }

        void websocket_server::close()
        {
            if (context_ != NULL) {
                lws_context_destroy(context_);
                context_ = NULL;
            }
        }

        world_ptr server::world() const
        {
            return world_;
        }
    }
}