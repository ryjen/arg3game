#include "interpreter.h"
#include "command.h"
#include "location.h"

namespace arg3
{
    namespace game
    {
        interpreter *interpreter::instance()
        {
            static interpreter theinterpreter;

            return &theinterpreter;
        }

        interpreter::interpreter()
        {
            add("look", new look_command());

            move_command *moveCmd = new move_command();
            for (int i = 0; i < DIR_MAX; i++) {
                add(direction_names[i], moveCmd);
            }
            add("shutdown", new shutdown_command());
        }

        interpreter &interpreter::add(const string &keyword, command *c)
        {
            commands_[keyword] = c;
            return *this;
        }

        void interpreter::execute(character_ptr ch, argument argument)
        {
            string keyword = argument.next();

            if (commands_.count(keyword) == 0) {
                ch->writeln(format("Unknown command {0}", keyword));
                return;
            }
            commands_.at(keyword)->execute(keyword, ch, argument);
        }
    }
}