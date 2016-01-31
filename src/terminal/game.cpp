#include "game.h"
#include "area.h"
#include "server.h"
#include <algorithm>
#include "exception.h"

namespace arg3
{
    namespace game
    {
        game *game::instance()
        {
            static game anInstance;

            return &anInstance;
        }

        game::game() : pollFrequency_(4)
        {
        }

        int game::run()
        {
            struct timeval last_time;

            gettimeofday(&last_time, NULL);

            log::debug("loading...");

            init();

            log::debug("starting servers..");

            for (auto &server : servers_) {
                server->start();
            }

            while (1) {
                for (auto &server : servers_) {
                    if (server->can_poll(&last_time, pollFrequency_)) {
                        server->poll();
                    }
                }
            }

            return EXIT_SUCCESS;
        }

        void game::on_start(net::socket_server *server)
        {
        }

        void game::on_poll(net::socket_server *server)
        {
        }

        void game::on_stop(net::socket_server *server)
        {
            log::info(format("shutting down port {0}", server->port()));

            for (auto it = servers_.begin(); it != servers_.end(); ++it) {
                if ((*it)->port() == server->port()) {
                    servers_.erase(it);
                    break;
                }
            }
        }

        void game::init()
        {
            db_instance.open("localhost");

            auto worlds = db::find_all<world>();

            if (worlds.size() == 0) {
                auto world = world::create_default();

                servers_.push_back(make_shared<telnet_server>(world, this));

                if (world->websocket_port()) {
                    servers_.push_back(make_shared<websocket_server>(world));
                }
            } else {
                log::trace(format("Done loading {0} world(s)", worlds.size()));

                for (auto &world : worlds) {
                    servers_.push_back(make_shared<telnet_server>(world, this));

                    if (world->websocket_port()) {
                        servers_.push_back(make_shared<websocket_server>(world));
                    }
                }
            }
        }
    }
}