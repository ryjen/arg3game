#ifndef ARG3_GAME_ACCOUNT_H
#define ARG3_GAME_ACCOUNT_H

#include "db.h"
#include "player.h"
#include <vector>

namespace arg3
{
    namespace game
    {
        class account : public record<account>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "accounts";
            constexpr static const char *const COL_LOGIN = "login";
            constexpr static const char *const COL_EMAIL = "email";
            constexpr static const char *const COL_PASSWD = "password";
#endif
            account();
            account(const account &account);
            virtual ~account();
            account &operator=(const account &account);

            static account_ptr find_by_login(const string &value);
            void set_playing(player_ptr value);
            void set_login(const string &value);
            string login() const;
            string password() const;
            string email() const;
            void set_email(const string &value);
            void set_password(const string &value);
            player_ptr playing();
            void to_storage(storage_builder &obj) const;
            void from_storage(const storage &obj);

           private:
            player_ptr playing_;
        };
    }
}

#endif
