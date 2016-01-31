#ifndef ARG3_GAME_CHARACTER_H
#define ARG3_GAME_CHARACTER_H

#ifndef SWIG
#include "db.h"
#include "scriptable.h"
#include "writable.h"
#include "location.h"
#endif

namespace arg3
{
    namespace game
    {
        class location;

        class character : public scriptable, public writable, public record<character>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "characters";
            constexpr static const char *const COL_NAME = "name";
#endif

            virtual ~character();

#ifndef SWIG
            character(character &&other);
            character &operator=(character &&other);
#endif
            character &operator=(const character &other);

            virtual void from_storage(const storage &obj);

            virtual void to_storage(storage_builder &obj) const;

            string name() const;
            void set_name(const string &value);

            void set_location(arg3::game::location *value);
            arg3::game::location *location() const;

           protected:
            character();

            character(const character &other);

           private:
            arg3::game::location *location_;
        };
    }
}

#endif
