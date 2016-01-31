#ifndef ARG3_GAME_OBJECT_H
#define ARG3_GAME_OBJECT_H

#include "entity.h"
#include "writable.h"
#include "scriptable.h"
#include "db.h"
#include "typedef.h"

namespace arg3
{
    namespace game
    {
        class character;
        class location;

        class object : public writable, public scriptable, public record<object>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "objects";
#endif
            object();
            object(const object &obj);
            virtual ~object();
            object &operator=(const object &obj);
#ifndef SWIG
            object &operator=(object &&obj);
            object(object &&obj);
            const char *swig_type_name() const;
#endif
            arg3::game::location *location() const;
            void set_location(arg3::game::location *place);

            object &write(const std::string &value);
            object &writeln();
            object &writeln(const std::string &value);
            object &write(void *buf, size_t sz);
            void to_storage(storage_builder &obj) const;
            void from_storage(const storage &obj);

           private:
            character *carriedBy_;
            arg3::game::location *location_;
        };
    }
}
#endif
