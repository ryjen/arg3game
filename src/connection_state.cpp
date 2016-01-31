#include "connection.h"
#include "connection_state.h"
#include "area.h"
#include "world.h"
#include "exception.h"

namespace arg3
{
    namespace game
    {
        connection_state::connection_state(game::connection *conn) : conn_(conn)
        {
            assert(conn_ != NULL);
        }

        connection_state &connection_state::writeln(const string &value)
        {
            conn_->writeln(value);
            return *this;
        }

        connection_state &connection_state::write(const string &value)
        {
            conn_->write(value);
            return *this;
        }

        connection_state &connection_state::writeln()
        {
            conn_->writeln();
            return *this;
        }

        connection *connection_state::connection() const
        {
            return conn_;
        }

        account_ptr connection_state::account() const
        {
            return conn_->account();
        }

        world_ptr connection_state::world() const
        {
            return conn_->world();
        }
    }
}