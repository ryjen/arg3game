#ifndef ARG3_GAME_TYPEDEF_H
#define ARG3_GAME_TYPEDEF_H

#include <memory>

namespace arg3
{
    namespace game
    {
        class location;
        class world;
        class character;
        class connection;
        class exit;
        class object;
        class area;
        class npc;
        class player;
        class account;

        typedef std::shared_ptr<location> location_ptr;
        typedef std::shared_ptr<world> world_ptr;
        typedef std::shared_ptr<character> character_ptr;
        typedef std::shared_ptr<connection> connection_ptr;
        typedef std::shared_ptr<exit> exit_ptr;
        typedef std::shared_ptr<object> object_ptr;
        typedef std::shared_ptr<area> area_ptr;
        typedef std::shared_ptr<npc> npc_ptr;
        typedef std::shared_ptr<player> player_ptr;
        typedef std::shared_ptr<account> account_ptr;

        template <typename T>
        std::shared_ptr<T> ptr(T *data)
        {
            return std::shared_ptr<T>(data);
        }
    }
}
#endif
