#include "connection.h"
#include "connection_state.h"
#include "area.h"
#include "world.h"
#include "log.h"
#include "exception.h"

namespace arg3
{
    namespace game
    {
        state_playing::state_playing(game::connection *conn) : connection_state(conn)
        {
        }

        void state_playing::prompt()
        {
        }

        void state_playing::execute(argument arg)
        {
        }

        state_login::state_login(game::connection *conn) : connection_state(conn)
        {
        }

        void state_login::prompt()
        {
        }

        void state_login::execute(argument arg)
        {
        }

        state_create_account::state_create_account(game::connection *conn) : connection_state(conn)
        {
        }

        void state_create_account::prompt()
        {
        }

        void state_create_account::execute(argument arg)
        {
        }

        state_ask_email::state_ask_email(game::connection *conn) : connection_state(conn)
        {
        }

        void state_ask_email::prompt()
        {
        }

        void state_ask_email::execute(argument arg)
        {
        }

        state_confirm_email::state_confirm_email(game::connection *conn) : connection_state(conn)
        {
        }

        void state_confirm_email::prompt()
        {
        }

        void state_confirm_email::execute(argument arg)
        {
        }

        state_create_password::state_create_password(game::connection *conn) : connection_state(conn)
        {
        }

        void state_create_password::prompt()
        {
        }

        void state_create_password::execute(argument arg)
        {
        }

        void state_character_selection::prompt()
        {
        }

        state_confirm_password::state_confirm_password(game::connection *conn) : connection_state(conn)
        {
        }

        void state_confirm_password::prompt()
        {
        }

        void state_confirm_password::execute(argument arg)
        {
        }

        state_ask_password::state_ask_password(game::connection *conn) : connection_state(conn)
        {
        }

        void state_ask_password::prompt()
        {
        }

        void state_ask_password::execute(argument arg)
        {
        }

        state_character_selection::state_character_selection(game::connection *conn) : connection_state(conn)
        {
        }

        void state_character_selection::execute(argument arg)
        {
        }

        state_create_character::state_create_character(game::connection *conn) : connection_state(conn)
        {
        }

        void state_create_character::prompt()
        {
        }

        void state_create_character::execute(argument arg)
        {
        }
    }
}