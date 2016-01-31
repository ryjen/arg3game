#ifndef ARG3_GAME_EXIT_H
#define ARG3_GAME_EXIT_H

#include "db.h"
#include "direction.h"
#include "typedef.h"

namespace arg3
{
    namespace game
    {
        class exit : public record<exit>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "exits";
            constexpr static const char *const COL_TO_LOCATION = "to_location_id";
            constexpr static const char *const COL_FROM_LOCATION = "from_location_id";
            constexpr static const char *const COL_DIRECTION = "direction";
#endif
            exit();
            exit(const exit &e);
            exit(exit &&e);
            ~exit();
            exit &operator=(const exit &e);
            exit &operator=(exit &&e);
            location *to();
            location *from() const;
            void set_to(location *loc);
            void set_from(location *loc);
            direction_t direction() const;
            void set_direction(direction_t d);

            void to_storage(storage_builder &obj) const;
            void from_storage(const storage &obj);

            bool is_valid() const;

           private:
            location *to_;
            location *from_;
            direction_t direction_;
        };
    }
}

#endif
