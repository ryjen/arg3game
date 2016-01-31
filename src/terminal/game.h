#ifndef ARG3_GAME_TERMINAL_GAME_H
#define ARG3_GAME_TERMINAL_GAME_H

#include <arg3net/socket_server.h>

namespace arg3
{
    namespace game
    {
        class server;

        class game : public arg3::net::socket_server_listener
        {
           public:
            static game *instance();
            int run();
            int pollFrequency_;

           private:
            game();
            void init();
            void on_poll(arg3::net::socket_server *server);
            void on_start(arg3::net::socket_server *server);
            void on_stop(arg3::net::socket_server *server);
            vector<shared_ptr<server>> servers_;
        };
    }
}

#endif
