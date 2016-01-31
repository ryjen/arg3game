#ifndef ARG3_GAME_INTERPRETER_H
#define ARG3_GAME_INTERPRETER_H

#include <string>
#include <map>
#include <arg3str/argument.h>

#include "typedef.h"
#include "util.h"

namespace arg3
{
    namespace game
    {
        class command;

        class interpreter
        {
           public:
            static interpreter *instance();

            interpreter &add(const std::string &keyword, command *c);

            void execute(character_ptr ch, argument argument);

           private:
            interpreter();

            std::map<std::string, command *, no_case_less> commands_;
        };
    }
}

#endif
