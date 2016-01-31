#ifndef ARG3_GAME_SCRIPT_H
#define ARG3_GAME_SCRIPT_H

#include <string>
#include <cassert>
#include "scriptable.h"
#include "db.h"

extern "C" {

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

extern int luaopen_swig(lua_State *L);  // declare the wrapped module
}
namespace arg3
{
    namespace game
    {
        class script : public record<script>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "scripts";
#endif
            void execute();

            virtual ~script();

            script();
            script(const std::string &value);
            script(const script &other) = delete;
            script(script &&other) = delete;
            script &operator=(const script &other) = delete;
            script &operator=(script &&other) = delete;

            void push(const char *name, scriptable *obj);

            std::string get_string(int pos) const;

            void to_storage(storage_builder &obj) const;
            void from_storage(const storage &obj);

           private:
            lua_State *state_;
            std::string value_;
        };
    }
}
#endif
