#ifndef ARG3_GAME_CONNECTION_H
#define ARG3_GAME_CONNECTION_H

#include <arg3net/telnet_socket.h>
#include "writable.h"
#include <arg3str/argument.h>
#include "typedef.h"
#include <libwebsockets.h>
#include <arg3str/buffer.h>

namespace arg3
{
    namespace game
    {
        class player;
        class world;
        class connection_state;

        class connection
        {
           private:
            world_ptr world_;

            account_ptr account_;

            shared_ptr<connection_state> state_;

           public:
            connection();
            ~connection();
            connection(const connection &conn) = delete;
            connection(connection &&conn);

            account_ptr account() const;
            void set_account(account_ptr value);

            virtual void close() = 0;

            void process_input(const string &value);

            world_ptr world() const;
            void set_world(world_ptr world);

            connection &operator=(const connection &other) = delete;

            connection &operator=(connection &&other);

            virtual void show_prompt() = 0;

            virtual void show_welcome() = 0;

            virtual connection &write(const std::string &value) = 0;
            virtual connection &write(void *buf, size_t sz) = 0;
            connection &writeln();
            connection &writeln(const std::string &value);
            connection &operator<<(const std::string &value);

            void set_state(shared_ptr<connection_state> state);

            const shared_ptr<connection_state> state() const;

            virtual void start_enter_password() = 0;
            virtual void end_enter_password() = 0;
        };

        class websocket_connection : public connection, public buffered_reader, public buffered_writer
        {
           public:
            websocket_connection(struct lws *wsi);
            connection &write(const std::string &value);
            connection &write(void *buf, size_t sz);

            bool read_to_buffer();
            bool write_from_buffer();

            void close();
            void start_enter_password();
            void end_enter_password();
            void show_welcome();
            void show_prompt();

           private:
            struct lws *sock_;
        };
    }
}
#endif
