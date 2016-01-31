#include "player.h"
#include "connection.h"
#include "util.h"
#include "account.h"

namespace arg3
{
    namespace game
    {
        player::player() : conn_(NULL), account_(NULL)
        {
        }

        player::player(const player &other) : character(other), conn_(other.conn_), account_(other.account_)
        {
        }

        player::~player()
        {
        }

        player::player(player &&other) : character(std::move(other)), conn_(other.conn_), account_(other.account_)
        {
            other.conn_ = NULL;
            other.account_ = NULL;
        }

        player &player::operator=(player &&other)
        {
            character::operator=(std::move(other));
            conn_ = other.conn_;
            account_ = other.account_;
            other.conn_ = NULL;
            other.account_ = NULL;
            return *this;
        }

        player &player::operator=(const player &other)
        {
            character::operator=(other);
            conn_ = other.conn_;
            account_ = other.account_;
            return *this;
        }

        void player::set_connection(connection *c)
        {
            conn_ = c;
        }

        const char *player::swig_type_name() const
        {
            return "arg3::game::player *";
        }

        game::account *player::account() const
        {
            return account_;
        }

        void player::set_account(game::account *value)
        {
            account_ = value;
        }

        player &player::writeln()
        {
            if (conn_ != NULL) conn_->writeln();
            return *this;
        }
        player &player::writeln(const std::string &value)
        {
            if (conn_ != NULL) conn_->writeln(value);
            return *this;
        }

        player &player::write(const std::string &value)
        {
            if (conn_ != NULL) {
                conn_->write(value);
            }
            return *this;
        }

        player &player::operator<<(const std::string &value)
        {
            if (conn_ != NULL) {
                conn_->write(value);
            }
            return *this;
        }
        player &player::write(void *buf, size_t sz)
        {
            if (conn_ != NULL) {
                conn_->write(buf, sz);
            }
            return *this;
        }

        void player::to_storage(storage_builder &obj) const
        {
            character::to_storage(obj);

            account()->store_reference(obj);
        }

        void player::from_storage(const storage &obj)
        {
            character::from_storage(obj);

            // account_ = db::from_reference<dlm::account>(obj, db());
        }
    }
}