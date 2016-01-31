#ifndef ARG3_GAME_PLAYER_H
#define ARG3_GAME_PLAYER_H

#include "character.h"
namespace arg3
{
    namespace game
    {
        class connection;
        class account;

        class player : public character
        {
           public:
            player();
            player(const player &other);
            virtual ~player();
#ifndef SWIG
            player(player &&other);
            player &operator=(player &&other);
            const char *swig_type_name() const;
#endif
            player &operator=(const player &other);
            player &writeln();
            player &writeln(const std::string &value);
            player &write(const std::string &value);
            player &write(void *buf, size_t sz);
            player &operator<<(const std::string &value);
            void set_connection(connection *c);

            game::account *account() const;
            void set_account(game::account *value);

            void to_storage(storage_builder &obj) const;
            void from_storage(const storage &obj);

           private:
            connection *conn_;
            game::account *account_;
        };
    }
}

#endif
