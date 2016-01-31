#include "area.h"
#include "server.h"
#include "connection.h"

using namespace arg3::net;

namespace arg3
{
    namespace game
    {
        connection_factory connection_factory::instance_;

        connection_factory *connection_factory::instance()
        {
            return &instance_;
        }

        std::shared_ptr<buffered_socket> connection_factory::create_socket(socket_server *sockserver, SOCKET sock,
                                                                           const struct sockaddr_storage &addr)
        {
            server *server = dynamic_cast<arg3::game::server *>(sockserver);

            auto conn = make_shared<telnet_connection>(sock, addr);

            conn->set_world(server->world());

            return conn;
        }


        bool telnet_server::start()
        {
            return socket_server::listen(world()->port(), 10);
        }

        void telnet_server::poll()
        {
            socket_server::poll();
        }

        void telnet_server::on_start()
        {
            socket_server::on_start();

            log::info(arg3::format("server started on port {0}", port()));
        }

        void telnet_server::on_stop()
        {
            socket_server::on_stop();

            log::info(arg3::format("server stopped on port {0}", port()));
        }

        void telnet_server::on_poll()
        {
        }

        telnet_server::telnet_server(world_ptr world) : socket_server(connection_factory::instance()), server(world)
        {
        }

        telnet_server::telnet_server(world_ptr world, socket_server_listener *listener) : socket_server(connection_factory::instance()), server(world)
        {
            add_listener(listener);
        }

        int telnet_server::port() const
        {
            return socket_server::port();
        }

        void telnet_server::close()
        {
            socket_server::close();
        }
    }
}