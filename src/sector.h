#ifndef ARG3_GAME_SECTOR_H
#define ARG3_GAME_SECTOR_H

namespace arg3
{
    namespace game
    {
        typedef enum {
            SECTOR_NONE,
            SECTOR_INSIDE,
            SECTOR_CITY,
            SECTOR_FIELD,
            SECTOR_FOREST,
            SECTOR_HILLS,
            SECTOR_MOUNTAIN,
            SECTOR_WATER,
            SECTOR_AIR,
            SECTOR_DESERT,
            SECTOR_JUNGLE,
            SECTOR_ROAD,
            SECTOR_PATH,
            SECTOR_CAVE,
            SECTOR_SWAMP,
            SECTOR_MAX
        } sector_t;
    }
}
#endif
