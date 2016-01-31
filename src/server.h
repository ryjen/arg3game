#ifndef ARG3_GAME_SERVER_H
#define ARG3_GAME_SERVER_H

#include <arg3net/socket_server.h>
#include <arg3net/socket_factory.h>
#include "connection.h"
#include "world.h"
#include <list>
#include <libwebsockets.h>

namespace arg3
{
    namespace game
    {
        class server
        {
           public:
            server(world_ptr world);
            world_ptr world() const;
            virtual void close() = 0;
            virtual void poll() = 0;
            virtual int port() const = 0;
            virtual bool start() = 0;
            bool can_poll(struct timeval *last_time, int pollFrequency);

           private:
            world_ptr world_;
            shared_ptr<database> db_;
        };

        class websocket_server : public server
        {
           public:
            websocket_server(world_ptr world);
            websocket_server(world_ptr world, net::socket_server_listener *listener);
            void close();
            int port() const;
            void poll();
            void add_websocket(shared_ptr<websocket_connection> conn);
            void remove_websocket(shared_ptr<websocket_connection> conn);
            vector<shared_ptr<websocket_connection>> &websockets();
            bool start();

           private:
            struct lws_context *context_;
            vector<std::shared_ptr<websocket_connection>> websockets_;
        };
    }
}

#endif
