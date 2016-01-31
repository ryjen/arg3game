
#include "script.h"
#include <arg3/log.h>
#include <arg3format/format.h>
#include "character.h"

#ifndef SWIG
#include "swig.h"
#endif

namespace arg3
{
    namespace game
    {
        static lua_State *init_lua()
        {
            lua_State *state = luaL_newstate();
            luaopen_base(state);
            luaopen_swig(state);
            return state;
        }

        script::script() : state_(init_lua())
        {
        }

        script::script(const string &value) : state_(init_lua()), value_(value)
        {
        }

        script::~script()
        {
            if (state_ != NULL) {
                lua_close(state_);
                state_ = NULL;
            }
        }

        void script::push(const char *name, scriptable *obj)
        {
            SWIG_Lua_NewPointerObj(state_, obj, SWIG_TypeQuery(state_, obj->swig_type_name()), 0);
            lua_setglobal(state_, name);
        }

        void script::to_storage(storage_builder &obj) const
        {
        }

        void script::from_storage(const storage &obj)
        {
        }

        void script::execute()
        {
            if (luaL_dostring(state_, value_.c_str())) {
                arg3::log::error(arg3::format("script: {0}", lua_tostring(state_, -1)));
            }
        }

        string script::get_string(int pos) const
        {
            return lua_tostring(state_, -pos);
        }
    }
}