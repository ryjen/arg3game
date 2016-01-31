#include "account.h"


namespace arg3
{
    namespace game
    {
        account::account() : playing_(nullptr)
        {
        }

        account::account(const account &account) : record(account), playing_(account.playing_)
        {
        }

        account::~account()
        {
        }

        account &account::operator=(const account &other)
        {
            record::operator=(other);
            playing_ = other.playing_;
            return *this;
        }

        void account::to_storage(storage_builder &obj) const
        {
            obj << COL_LOGIN << login();
            obj << COL_EMAIL << email();
            obj << COL_PASSWD << password();
        }

        void account::from_storage(const storage &obj)
        {
            set_login(obj[COL_LOGIN].str());
            set_email(obj[COL_EMAIL].str());
            set_password(obj[COL_PASSWD].str());
        }

        shared_ptr<account> account::find_by_login(const string &value)
        {
            auto res = db::find<account>(BSON(COL_LOGIN << value));

            if (res.size()) return res[0];

            return nullptr;
        }

        void account::set_playing(player_ptr value)
        {
            playing_ = value;
        }

        void account::set_login(const string &value)
        {
            set(COL_LOGIN, value);
        }

        string account::login() const
        {
            return get<string>(COL_LOGIN);
        }

        string account::email() const
        {
            return get<string>(COL_EMAIL);
        }

        void account::set_email(const string &value)
        {
            set(COL_EMAIL, value);
        }

        string account::password() const
        {
            return get<string>(COL_PASSWD);
        }

        void account::set_password(const string &value)
        {
            set(COL_PASSWD, value);
        }

        player_ptr account::playing()
        {
            return playing_;
        }
    }
}
