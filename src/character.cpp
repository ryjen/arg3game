#include "character.h"
#include "location.h"

namespace arg3
{
    namespace game
    {
        character::character() : location_(NULL)
        {
        }

        character::character(const character &other) : record(other), location_(other.location_)
        {
        }

        character::~character()
        {
        }

        character::character(character &&other) : record(std::move(other)), location_(other.location_)
        {
        }

        character &character::operator=(character &&other)
        {
            entity::operator=(std::move(other));

            record::operator=(std::move(other));

            location_ = other.location_;

            return *this;
        }

        character &character::operator=(const character &other)
        {
            entity::operator=(other);

            record::operator=(other);

            location_ = other.location_;

            return *this;
        }

        void character::from_storage(const storage &obj)
        {
            set_name(obj[COL_NAME].str());

            // location_ = db::from_reference<game::location>(obj, db()).get();
        }

        void character::to_storage(storage_builder &obj) const
        {
            obj << COL_NAME << name();

            if (this->location()) {
                this->location()->store_reference(obj);
            }
        }

        string character::name() const
        {
            return record::get<string>(COL_NAME);
        }

        void character::set_name(const string &value)
        {
            record::set(COL_NAME, value);
        }

        void character::set_location(game::location *value)
        {
            location_ = value;
        }
        game::location *character::location() const
        {
            return location_;
        }
    }
}