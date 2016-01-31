#include "connection.h"
#include "command.h"
#include "interpreter.h"
#include <arg3net/protocol.h>
#include "connection_state.h"

namespace arg3
{
    namespace game
    {
        telnet_connection::telnet_connection(net::SOCKET sock, const struct sockaddr_storage &addr) : telnet_socket(sock, addr)
        {
            set_state(make_shared<state_login>(this));
        }

        void telnet_connection::show_prompt()
        {
            state()->prompt();
        }

        void telnet_connection::show_welcome()
        {
            buffered_socket::writeln("Welcome to the game");

            show_prompt();
        }
        void telnet_connection::close()
        {
            buffered_socket::close();
        }

        void telnet_connection::on_will_read()
        {
            telnet_socket::on_will_read();
        }

        void telnet_connection::on_did_read()
        {
            process_input(readln());
        }

        void telnet_connection::on_will_write()
        {
            telnet_socket::on_will_write();
        }

        void telnet_connection::start_enter_password()
        {
            send_telopt(net::telnet::WILL, net::telnet::ECHO);
        }

        void telnet_connection::end_enter_password()
        {
            send_telopt(net::telnet::WONT, net::telnet::ECHO);
        }

        void telnet_connection::on_did_write()
        {
            telnet_socket::on_did_write();
        }

        void telnet_connection::on_telopt(socket::data_type type, socket::data_type option)
        {
            log::trace(format("GOT TELOPT: {0} {1}", (int)type, (int)option));
            switch (type) {
            }
        }

        void telnet_connection::on_sub_neg(socket::data_type type, const socket::data_buffer &parameters)
        {
            log::trace(format("GOT SUBNEG: {0}", type));
            switch (type) {
            }
        }

        void telnet_connection::on_connect()
        {
            log::trace(format("{0} connected", ip()));

            show_welcome();
        }

        void telnet_connection::on_close()
        {
            connection::writeln("Goodbye!");
        }


        connection &telnet_connection::write(const std::string &value)
        {
            buffered_socket::write(value);
            return *this;
        }
        connection &telnet_connection::write(void *buf, size_t sz)
        {
            buffered_socket::send(buf, sz);
            return *this;
        }
    }
}