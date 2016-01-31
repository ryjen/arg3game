#include "command.h"
#include "direction.h"
#include "character.h"
#include "location.h"
#include "exception.h"
#include "exit.h"
#include "util.h"
#include <arg3str/buffer.h>
#include "interpreter.h"

#define COMMAND(name) void name##_command::execute(const string &keyword, character_ptr ch, argument arg)

namespace arg3
{
    namespace game
    {
        int command::min_level() const
        {
            return 0;
        }

        COMMAND(move)
        {
            if (ch->location() == nullptr) {
                log::error(format("character {0} with no location", ch->name()));
                return;
            }
            direction_t d = direction_lookup(keyword);

            assert(d != DIR_MAX);

            auto loc = ch->location()->exit(d);

            if (loc == nullptr || loc->to() == nullptr) {
                ch->writeln("No exit in that direction.");
                return;
            }

            if (ch->location() != nullptr) {
                ch->location()->remove(ch);
            }

            loc->to()->add(ch);

            interpreter::instance()->execute(ch, string("look"));
        }

        COMMAND(look)
        {
            auto loc = ch->location();

            if (loc == nullptr) {
                ch->writeln("Uh oh, you are nowhere.");
                return;
            }

            show_room(ch, loc);
        }

        void show_room(character_ptr ch, location *loc)
        {
            ch->writeln(loc->name());

            buffer buf;

            for (int d = DIR_START; d < DIR_MAX; d++) {
                auto e = loc->exit(static_cast<direction_t>(d));

                if (e == nullptr) {
                    continue;
                }

                buf << direction_names[e->direction()];

                buf << ",";
            }

            if (!buf.empty()) {
                buf.remove(buf.length() - 1);

                ch->write("[Exits: ") << buf << "]\n";
            }
        }

        COMMAND(shutdown)
        {
            throw shutdown_exception();
        }
    }
}