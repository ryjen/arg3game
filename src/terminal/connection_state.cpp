#include "connection.h"
#include "connection_state.h"
#include "area.h"
#include "interpreter.h"
#include "world.h"
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
            writeln(format("Welcome, {0}", account()->playing()->name()));

            auto defaultArea = world()->begin();

            if (defaultArea == world()->end()) {
                throw game_exception("No default area");
            }

            auto defaultRoom = (*defaultArea)->begin();

            if (defaultRoom == (*defaultArea)->end()) {
                throw game_exception("No default room");
            }

            account()->playing()->set_location(defaultRoom->get());

            // show_room(account()->playing(), account()->playing()->location());
        }

        void state_playing::execute(argument arg)
        {
            if (!arg.empty()) {
                interpreter::instance()->execute(account()->playing(), arg);
            }
        }

        state_login::state_login(game::connection *conn) : connection_state(conn)
        {
        }

        void state_login::prompt()
        {
            write("Login: ");
        }

        void state_login::execute(argument arg)
        {
            auto a = account::find_by_login(arg);

            if (a == nullptr) {
                connection()->set_account(make_shared<game::account>());
                account()->set_login(arg);
                transition<state_create_account>();
            } else {
                connection()->set_account(a);
                transition<state_ask_password>();
            }
        }

        state_create_account::state_create_account(game::connection *conn) : connection_state(conn)
        {
        }

        void state_create_account::prompt()
        {
            write("Would you like to create an account? (Y/n)");
        }

        void state_create_account::execute(argument arg)
        {
            switch (arg.empty() ? 'Y' : toupper(arg[0])) {
                case 'Y':
                    writeln(format("Creating account for {0}.", account()->login()));
                    transition<state_ask_email>();
                    break;
                case 'N':
                    transition<state_login>();
                    break;
            }
        }

        state_ask_email::state_ask_email(game::connection *conn) : connection_state(conn)
        {
        }

        void state_ask_email::prompt()
        {
            write("What is your email address? ");
        }

        void state_ask_email::execute(argument arg)
        {
            account()->set_email(arg);

            transition<state_confirm_email>();
        }

        state_confirm_email::state_confirm_email(game::connection *conn) : connection_state(conn)
        {
        }

        void state_confirm_email::prompt()
        {
            write("Please re-enter your email address: ");
        }

        void state_confirm_email::execute(argument arg)
        {
            if (account()->email() != arg) {
                writeln("Those addresses do not match.");
                transition<state_ask_email>();
            } else {
                transition<state_create_password>();
            }
        }

        state_create_password::state_create_password(game::connection *conn) : connection_state(conn)
        {
        }

        void state_create_password::prompt()
        {
            write("Please enter a password: ");
            connection()->start_enter_password();
        }

        void state_create_password::execute(argument arg)
        {
            if (arg.empty()) {
                writeln("Please enter a password: ");
                return;
            }

            account()->set_password(arg);

            transition<state_confirm_password>();
        }

        void state_character_selection::prompt()
        {
            writeln("Character Options:");
            writeln("C) Create New");

            auto players = account()->find_all_by_ref<player>();

            int count = 0;

            for (auto &player : players) {
                writeln(format("{0}) {1}", ++count, player->name()));
            }

            writeln();
            write("Choose an option: ");
        }

        state_confirm_password::state_confirm_password(game::connection *conn) : connection_state(conn)
        {
        }

        void state_confirm_password::prompt()
        {
            write("Please re-enter your password: ");
        }

        void state_confirm_password::execute(argument arg)
        {
            if (account()->password() != arg) {
                write("Passwords don't match.");
                transition<state_create_password>();
            } else {
                connection()->end_enter_password();
                transition<state_character_selection>();
            }
        }

        state_ask_password::state_ask_password(game::connection *conn) : connection_state(conn)
        {
        }

        void state_ask_password::prompt()
        {
            write("Password: ");
            connection()->start_enter_password();
        }

        void state_ask_password::execute(argument arg)
        {
            if (account()->password() != arg) {
                writeln("Incorrect password.");

                int retries = account()->get<int>("password_retries");

                if (retries == 2) {
                    writeln("Your have tried this password too many times. Your ip has been logged.");
                    account()->set("password_retries", 0);
                    connection()->end_enter_password();
                    transition<state_login>();
                } else {
                    account()->set("password_retries", retries + 1);
                    write("Password: ");
                }
            } else {
                connection()->end_enter_password();
                transition<state_character_selection>();
            }
        }

        state_character_selection::state_character_selection(game::connection *conn) : connection_state(conn)
        {
        }

        void state_character_selection::execute(argument arg)
        {
            if (arg.empty()) {
                write("Sorry which option? ");
                return;
            }

            switch (toupper(arg[0])) {
                case 'C':
                    transition<state_create_character>();
                    break;
                default: {
                    int index;
                    try {
                        index = arg.next_number();
                    } catch (const std::exception &e) {
                        index = 0;
                    }
                    auto &&players = account()->find_all_by_ref<player>();

                    if (index <= 0 && index > players.size()) {
                        writeln("No such option.");
                        return;
                    }

                    auto &ch = players[index - 1];

                    ch->set_account(account().get());

                    account()->set_playing(ch);

                    ch->set_connection(connection());

                    transition<state_playing>();
                    break;
                }
            }
        }

        state_create_character::state_create_character(game::connection *conn) : connection_state(conn)
        {
        }

        void state_create_character::prompt()
        {
            write("By what name shall this character be known? ");
        }

        void state_create_character::execute(argument arg)
        {
            auto ch = make_shared<player>();

            ch->set_connection(connection());

            ch->set_name(arg);

            account()->set_playing(ch);

            ch->set_account(account().get());

            account()->save();

            ch->save();

            transition<state_playing>();
        }
    }
}