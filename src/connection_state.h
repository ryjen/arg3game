#ifndef ARG3_GAME_CONNECTION_STATE_H
#define ARG3_GAME_CONNECTION_STATE_H

#include <memory>
#include "account.h"
#include <arg3str/argument.h>

namespace arg3
{
    namespace game
    {
        class connection_state
        {
           protected:
            arg3::game::connection *conn_;

           public:
            connection_state(arg3::game::connection *conn);
            virtual void prompt() = 0;
            virtual void execute(argument arg) = 0;

            template <typename T>
            void transition()
            {
                auto state = make_shared<T>(conn_);
                conn_->set_state(state);
                state->prompt();
            }

            connection_state &writeln(const string &value);
            connection_state &write(const string &value);
            connection_state &writeln();

            arg3::game::connection *connection() const;

            account_ptr account() const;

            world_ptr world() const;
        };
    }
}

#endif
