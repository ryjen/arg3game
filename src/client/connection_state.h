#ifndef ARG3_GAME_CLIENT_CONNECTION_STATE_H
#define ARG3_GAME_CLIENT_CONNECTION_STATE_H

namespace arg3
{
    namespace game
    {
        class state_playing : public connection_state
        {
           public:
            state_playing(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };

        class state_login : public connection_state
        {
           public:
            state_login(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };

        class state_create_account : public connection_state
        {
           public:
            state_create_account(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };

        class state_ask_email : public connection_state
        {
           public:
            state_ask_email(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };

        class state_confirm_email : public connection_state
        {
           public:
            state_confirm_email(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };

        class state_create_password : public connection_state
        {
           public:
            state_create_password(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };

        class state_ask_password : public connection_state
        {
           public:
            state_ask_password(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };
        class state_confirm_password : public connection_state
        {
           public:
            state_confirm_password(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };
        class state_create_character : public connection_state
        {
           public:
            state_create_character(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };
        class state_character_selection : public connection_state
        {
           public:
            state_character_selection(game::connection *conn);
            void prompt();
            void execute(argument arg);
        };
    }
}

#endif
