#ifndef ARG3_GAME_DUNGEON_H
#define ARG3_GAME_DUNGEON_H

#include <string>
#include <vector>
#include <memory>
#include "direction.h"

namespace arg3
{
    namespace game
    {
        class area;
        class location;

        class dungeon
        {
           private:
            /*int xmax;
            int ymax;*/

            int xsize_;
            int ysize_;

            int objects_;

            int chanceRoom_;
            // int chanceCorridor_;

            int *dungeon_map_;

            long oldseed_;

            enum { tileUnused = 0, tileDirtWall, tileDirtFloor, tileStoneWall, tileCorridor, tileDoor, tileUpStairs, tileDownStairs, tileChest };

            void set_cell(int x, int y, int celltype);
            int cell(int x, int y) const;

            int rand(int min, int max);

            bool make_corridor(int x, int y, int lenght, int direction);
            bool make_room(int x, int y, int xlength, int ylength, int direction);

            shared_ptr<location> add_location(shared_ptr<area> area, int x, int y) const;
            void link_location(shared_ptr<area> area, shared_ptr<location> from, shared_ptr<location> to, direction_t dir) const;

           public:
            shared_ptr<area> to_area(const std::string &name) const;

            bool generate(int inx, int iny, int inobj);

            dungeon(int chanceRoom = 75);

            string to_string() const;

            vector<vector<int>> to_map() const;
        };
    }
}

#endif