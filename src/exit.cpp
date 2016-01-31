#include "exit.h"
#include "location.h"
#include "area.h"
#include "world.h"

namespace arg3
{
    namespace game
    {
        exit::exit() : to_(NULL), from_(NULL), direction_(DIR_MAX)
        {
        }
        exit::exit(const exit &e) : record(e), to_(e.to_), from_(e.from_), direction_(e.direction_)
        {
        }
        exit::exit(exit &&e) : record(e), to_(e.to_), from_(e.from_), direction_(e.direction_)
        {
            e.to_ = NULL;
            e.from_ = NULL;
            e.direction_ = DIR_MAX;
        }

        exit::~exit()
        {
        }

        exit &exit::operator=(const exit &e)
        {
            record::operator=(e);
            to_ = e.to_;
            from_ = e.from_;
            direction_ = e.direction_;
            return *this;
        }

        exit &exit::operator=(exit &&e)
        {
            record::operator=(std::move(e));
            to_ = e.to_;
            from_ = e.from_;
            direction_ = e.direction_;
            e.to_ = NULL;
            e.from_ = NULL;
            e.direction_ = DIR_MAX;
            return *this;
        }

        location *exit::to()
        {
            if (to_ == NULL && from_ != NULL && from_->area() != NULL && from_->area()->world() != NULL && has(COL_TO_LOCATION)) {
                to_ = from_->area()->world()->find_location(db::reference_id_name<location>(), get<string>(COL_TO_LOCATION)).get();
            }

            return to_;
        }

        void exit::set_to(location *loc)
        {
            to_ = loc;
        }

        void exit::set_from(location *loc)
        {
            from_ = loc;
        }

        location *exit::from() const
        {
            return from_;
        }

        direction_t exit::direction() const
        {
            return direction_;
        }

        void exit::set_direction(direction_t value)
        {
            direction_ = value;
        }

        bool exit::is_valid() const
        {
            return to_ && to_->is_saved() && from_ && from_->is_saved();
        }

        void exit::to_storage(storage_builder &obj) const
        {
            if (to_) {
                to_->store_reference(COL_TO_LOCATION, obj);
            }
            if (from_) {
                from_->store_reference(COL_FROM_LOCATION, obj);
            }

            obj << COL_DIRECTION << direction_names[direction_];
        }

        void exit::from_storage(const storage &obj)
        {
            set(COL_TO_LOCATION, obj[COL_TO_LOCATION]["$id"].str());
            set(COL_FROM_LOCATION, obj[COL_FROM_LOCATION]["$id"].str());
            set(COL_DIRECTION, direction_names[direction_]);

            set_direction(direction_lookup(obj[COL_DIRECTION].str()));
        }
    }
}