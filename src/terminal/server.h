#ifndef ARG3_GAME_TERMINAL_SERVER_H
#define ARG3_GAME_TERMINAL_SERVER_H

#include "../server.h"

namespace arg3
{
    namespace game
    {
        class connection_factory : public net::socket_factory
        {
           public:
            static connection_factory *instance();

            std::shared_ptr<net::buffered_socket> create_socket(net::socket_server *server, net::SOCKET sock, const struct sockaddr_storage &addr);

           private:
            static connection_factory instance_;
        };

        class telnet_server : public net::socket_server, public server
        {
           public:
            telnet_server(world_ptr world);
            telnet_server(world_ptr world, net::socket_server_listener *listener);
            int port() const;
            void on_start();
            void on_stop();
            void on_poll();
            bool start();
            void poll();
            void close();
        };
    }
}

#endif
