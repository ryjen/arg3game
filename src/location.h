#ifndef ARG3_GAME_LOCATION_H
#define ARG3_GAME_LOCATION_H

#include "character.h"
#include "object.h"
#include <list>
#include <array>
#include "db.h"
#include "direction.h"
#include "typedef.h"

namespace arg3
{
    namespace game
    {
        class area;
        class exit;

        class location : public writable, public scriptable, public record<location>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "locations";
            constexpr static const char *const COL_NAME = "name";
#endif
            location();
            location(const location &loc);
            location &operator=(const location &loc);
            ~location();
#ifndef SWIG
            location(location &&loc);
            location &operator=(location &&loc);
            const char *swig_type_name() const;
#endif
            location &add(character_ptr ch);
            location &add(object_ptr obj);
            location &add(exit_ptr e);


            location &remove(character_ptr ch);
            location &remove(object_ptr obj);

            location &write(const std::string &value);
            location &writeln();
            location &writeln(const std::string &value);
            location &write(void *buf, size_t sz);
            location &operator<<(const std::string &value);

            string name() const;
            void set_name(const string &value);

            arg3::game::area *area() const;
            void set_area(arg3::game::area *area);

            bool save();

            bool is_valid() const;

            exit_ptr exit(direction_t dir) const;

            void create_exit(direction_t dir, location *to);
            void remove_exit(direction_t dir);
            void remove_exit(exit_ptr e);

            void from_storage(const storage &obj);
            void to_storage(storage_builder &obj) const;

           private:
            list<character_ptr> characters_;
            list<object_ptr> objects_;
            arg3::game::area *area_;
            std::array<exit_ptr, DIR_MAX> exits_;
        };
    }
}

#endif