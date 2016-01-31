#include "connection.h"
#include "exception.h"
#include "util.h"
#include "player.h"
#include "area.h"
#include "world.h"
#include "server.h"
#include "account.h"
#include "connection_state.h"
#include <arg3net/protocol.h>

namespace arg3
{
    namespace game
    {
        connection::connection() : world_(nullptr), account_(nullptr), state_(nullptr)
        {
        }

        connection::connection(connection &&conn) : world_(std::move(conn.world_)), account_(std::move(conn.account_)), state_(conn.state_)
        {
            conn.account_ = nullptr;
            conn.world_ = nullptr;
        }

        connection::~connection()
        {
            if (account_ != nullptr) {
                account_ = nullptr;
            }
            if (world_ != nullptr) {
                world_ = nullptr;
            }
        }

        void connection::process_input(const string &value)
        {
            state_->execute(value);
        }

        void connection::set_state(shared_ptr<connection_state> state)
        {
            state_ = state;
            assert(state_ != nullptr);
        }

        connection &connection::operator=(connection &&other)
        {
            world_ = std::move(other.world_);
            account_ = std::move(other.account_);
            state_ = other.state_;
            other.world_ = nullptr;
            other.account_ = nullptr;

            return *this;
        }

        world_ptr connection::world() const
        {
            return world_;
        }

        void connection::set_world(world_ptr world)
        {
            world_ = world;
        }


        void connection::set_account(account_ptr value)
        {
            account_ = value;
        }

        account_ptr connection::account() const
        {
            return account_;
        }

        const shared_ptr<connection_state> connection::state() const
        {
            return state_;
        }

        connection &connection::operator<<(const std::string &value)
        {
            write(value);
            return *this;
        }


        connection &connection::writeln()
        {
            write("\r\n");
            return *this;
        }
        connection &connection::writeln(const std::string &value)
        {
            write(value);
            write("\r\n");
            return *this;
        }

        websocket_connection::websocket_connection(struct lws *wsi) : sock_(wsi)
        {
        }

        connection &websocket_connection::write(const string &value)
        {
            buffered_writer::write(value);

            return *this;
        }

        connection &websocket_connection::write(void *buf, size_t sz)
        {
            lws_write(sock_, (unsigned char *)buf, sz, LWS_WRITE_BINARY);
            return *this;
        }

        void websocket_connection::start_enter_password()
        {
            write("{% start_password %}");
        }

        void websocket_connection::end_enter_password()
        {
            write("{% end_password %}");
        }

        void websocket_connection::show_welcome()
        {
        }

        void websocket_connection::close()
        {
        }

        void websocket_connection::show_prompt()
        {
        }
        bool websocket_connection::read_to_buffer()
        {
            return true;
        }

        bool websocket_connection::write_from_buffer()
        {
            vector<unsigned char> buf(LWS_SEND_BUFFER_PRE_PADDING + output().size() + LWS_SEND_BUFFER_POST_PADDING);

            buf.insert(buf.begin() + LWS_SEND_BUFFER_PRE_PADDING, output().begin(), output().end());

            // send response
            // just notice that we have to tell where exactly our response starts. That's
            // why there's `buf[LWS_SEND_BUFFER_PRE_PADDING]` and how long it is.
            // we know that our response has the same length as request because
            // it's the same message in reverse order.
            lws_write(sock_, &buf[LWS_SEND_BUFFER_PRE_PADDING], output().size(), LWS_WRITE_TEXT);

            output().clear();

            return true;
        }
    }
}