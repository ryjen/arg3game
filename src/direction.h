#ifndef ARG3_GAME_DIRECTION_H
#define ARG3_GAME_DIRECTION_H

#include <arg3str/util.h>

namespace arg3
{
    namespace game
    {
        typedef enum { DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST, DIR_UP, DIR_DOWN, DIR_MAX, DIR_START = DIR_NORTH } direction_t;

        constexpr static const direction_t reverse_directions[] = {DIR_SOUTH, DIR_WEST, DIR_NORTH, DIR_EAST, DIR_DOWN, DIR_UP, DIR_MAX};

        constexpr static const char *const direction_names[] = {"North", "East", "South", "West", "Up", "Down"};

        inline direction_t direction_lookup(const std::string &name)
        {
            for (int i = 0; i < DIR_MAX; i++) {
                if (equals(name, direction_names[i])) return static_cast<direction_t>(i);
            }
            return DIR_MAX;
        }
    }
}
#endif
