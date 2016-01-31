#ifndef ARG3_GAME_TERMINAL_CONNECTION_H
#define ARG3_GAME_TERMINAL_CONNECTION_H

#include "../connection.h"
#include <arg3log/log.h>

namespace arg3
{
    namespace game
    {
        class telnet_connection : public net::telnet_socket, public connection
        {
           private:
            void on_telopt(socket::data_type type, socket::data_type option);
            void on_sub_neg(socket::data_type type, const socket::data_buffer &parameters);

           public:
            telnet_connection(arg3::net::SOCKET sock, const struct sockaddr_storage &addr);

            void on_will_read();

            void on_did_read();

            void on_will_write();

            void on_did_write();

            void on_connect();

            void close();

            void on_close();
            void show_welcome();
            void show_prompt();

            connection &write(const std::string &value);
            connection &write(void *buf, size_t sz);
            void start_enter_password();
            void end_enter_password();
        };
    }
}
#endif
