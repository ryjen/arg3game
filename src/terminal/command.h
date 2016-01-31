#ifndef ARG3_GAME_TERM_COMMAND_H
#define ARG3_GAME_TERM_COMMAND_H

#include <string>
#include <map>
#include <arg3str/argument.h>
#include "typedef.h"
#include "util.h"

#define DEF_COMMAND(name)                                           \
    class name##_command : public command                           \
    {                                                               \
       public:                                                      \
        void execute(const std::string &, character_ptr, argument); \
    }

namespace arg3
{
    namespace game
    {
        extern void show_room(character_ptr ch, location *room);

        class command
        {
           public:
            virtual int min_level() const;

            virtual void execute(const std::string &keyword, character_ptr ch, argument argument) = 0;

           private:
        };

        bool str_cmp(const std::string &, const std::string &);

        DEF_COMMAND(move);

        DEF_COMMAND(look);

        DEF_COMMAND(shutdown);
    }
}

#endif
