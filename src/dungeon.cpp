#include "area.h"
#include "location.h"
#include "dungeon.h"
#include "util.h"
#include "exit.h"

namespace arg3
{
    namespace game
    {
        void dungeon::set_cell(int x, int y, int celltype)
        {
            dungeon_map_[x + xsize_ * y] = celltype;
        }
        int dungeon::cell(int x, int y) const
        {
            return dungeon_map_[x + xsize_ * y];
        }

        int dungeon::rand(int min, int max)
        {
            time_t seed = time(NULL) + oldseed_;

            oldseed_ = seed;

            srand(seed);

            int n = max - min + 1;
            int i = ::rand() % n;

            if (i < 0) {
                i = -i;
            }

            return min + i;
        }

        bool dungeon::make_corridor(int x, int y, int lenght, int direction)
        {
            int len = rand(2, lenght);
            int floor = tileCorridor;
            int dir = 0;
            if (direction > 0 && direction < 4) {
                dir = direction;
            }

            int xtemp = 0;
            int ytemp = 0;

            switch (dir) {
                case 0: {
                    if (x < 0 || x > xsize_) {
                        return false;
                    } else {
                        xtemp = x;
                    }

                    for (ytemp = y; ytemp > (y - len); ytemp--) {
                        if (ytemp < 0 || ytemp > ysize_) {
                            return false;
                        }
                        if (cell(xtemp, ytemp) != tileUnused) {
                            return false;
                        }
                    }

                    for (ytemp = y; ytemp > (y - len); ytemp--) {
                        set_cell(xtemp, ytemp, floor);
                    }
                    break;
                }
                case 1: {
                    if (y < 0 || y > ysize_) {
                        return false;
                    } else {
                        ytemp = y;
                    }

                    for (xtemp = x; xtemp < (x + len); xtemp++) {
                        if (xtemp < 0 || xtemp > xsize_) {
                            return false;
                        }
                        if (cell(xtemp, ytemp) != tileUnused) {
                            return false;
                        }
                    }

                    for (xtemp = x; xtemp < (x + len); xtemp++) {
                        set_cell(xtemp, ytemp, floor);
                    }
                    break;
                }
                case 2: {
                    if (x < 0 || x > xsize_) {
                        return false;
                    } else {
                        xtemp = x;
                    }

                    for (ytemp = y; ytemp < (y + len); ytemp++) {
                        if (ytemp < 0 || ytemp > ysize_) {
                            return false;
                        }
                        if (cell(xtemp, ytemp) != tileUnused) {
                            return false;
                        }
                    }
                    for (ytemp = y; ytemp < (y + len); ytemp++) {
                        set_cell(xtemp, ytemp, floor);
                    }
                    break;
                }
                case 3: {
                    if (ytemp < 0 || ytemp > ysize_) {
                        return false;
                    } else {
                        ytemp = y;
                    }

                    for (xtemp = x; xtemp > (x - len); xtemp--) {
                        if (xtemp < 0 || xtemp > xsize_) {
                            return false;
                        }
                        if (cell(xtemp, ytemp) != tileUnused) {
                            return false;
                        }
                    }

                    for (xtemp = x; xtemp > (x - len); xtemp--) {
                        set_cell(xtemp, ytemp, floor);
                    }
                    break;
                }
            }
            // woot, we're still here! let's tell the other guys we're done!!
            return true;
        }

        bool dungeon::make_room(int x, int y, int xlength, int ylength, int direction)
        {
            // define the dimensions of the room, it should be at least 4x4 tiles (2x2 for walking on, the rest is walls)
            int xlen = rand(4, xlength);
            int ylen = rand(4, ylength);
            // the tile type it's going to be filled with
            int floor = tileDirtFloor;  // jordgolv..
            int wall = tileDirtWall;    // jordv????gg
            // choose the way it's pointing at
            int dir = 0;
            if (direction > 0 && direction < 4) {
                dir = direction;
            }

            switch (dir) {
                case 0:
                    // north
                    // Check if there's enough space left for it
                    for (int ytemp = y; ytemp > (y - ylen); ytemp--) {
                        if (ytemp < 0 || ytemp > ysize_) {
                            return false;
                        }
                        for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++) {
                            if (xtemp < 0 || xtemp > xsize_) {
                                return false;
                            }
                            if (cell(xtemp, ytemp) != tileUnused) {
                                return false;
                            }  // no space left...
                        }
                    }

                    // we're still here, build
                    for (int ytemp = y; ytemp > (y - ylen); ytemp--) {
                        for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++) {
                            // start with the walls
                            if (xtemp == (x - xlen / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (xtemp == (x + (xlen - 1) / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == y) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == (y - ylen + 1)) {
                                set_cell(xtemp, ytemp, wall);
                            }
                            // and then fill with the floor
                            else {
                                set_cell(xtemp, ytemp, floor);
                            }
                        }
                    }
                    break;
                case 1:
                    // east
                    for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++) {
                        if (ytemp < 0 || ytemp > ysize_) {
                            return false;
                        }
                        for (int xtemp = x; xtemp < (x + xlen); xtemp++) {
                            if (xtemp < 0 || xtemp > xsize_) {
                                return false;
                            }
                            if (cell(xtemp, ytemp) != tileUnused) {
                                return false;
                            }
                        }
                    }

                    for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++) {
                        for (int xtemp = x; xtemp < (x + xlen); xtemp++) {
                            if (xtemp == x) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (xtemp == (x + xlen - 1)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == (y - ylen / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == (y + (ylen - 1) / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            }

                            else {
                                set_cell(xtemp, ytemp, floor);
                            }
                        }
                    }
                    break;
                case 2:
                    // south
                    for (int ytemp = y; ytemp < (y + ylen); ytemp++) {
                        if (ytemp < 0 || ytemp > ysize_) {
                            return false;
                        }
                        for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++) {
                            if (xtemp < 0 || xtemp > xsize_) {
                                return false;
                            }
                            if (cell(xtemp, ytemp) != tileUnused) {
                                return false;
                            }
                        }
                    }

                    for (int ytemp = y; ytemp < (y + ylen); ytemp++) {
                        for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2); xtemp++) {
                            if (xtemp == (x - xlen / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (xtemp == (x + (xlen - 1) / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == y) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == (y + ylen - 1)) {
                                set_cell(xtemp, ytemp, wall);
                            }

                            else {
                                set_cell(xtemp, ytemp, floor);
                            }
                        }
                    }
                    break;
                case 3:
                    // west
                    for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++) {
                        if (ytemp < 0 || ytemp > ysize_) {
                            return false;
                        }
                        for (int xtemp = x; xtemp > (x - xlen); xtemp--) {
                            if (xtemp < 0 || xtemp > xsize_) {
                                return false;
                            }
                            if (cell(xtemp, ytemp) != tileUnused) {
                                return false;
                            }
                        }
                    }

                    for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2); ytemp++) {
                        for (int xtemp = x; xtemp > (x - xlen); xtemp--) {
                            if (xtemp == x) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (xtemp == (x - xlen + 1)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == (y - ylen / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            } else if (ytemp == (y + (ylen - 1) / 2)) {
                                set_cell(xtemp, ytemp, wall);
                            }

                            else {
                                set_cell(xtemp, ytemp, floor);
                            }
                        }
                    }
                    break;
            }

            // yay, all done
            return true;
        }

        shared_ptr<location> dungeon::add_location(area_ptr area, int x, int y) const
        {
            auto loc = make_shared<location>();
            loc->set_name(format("Location {0}-{1}", x, y));
            loc->set_area(area.get());
            area->add(loc);
            return loc;
        }

        void dungeon::link_location(area_ptr area, location_ptr from, location_ptr to, direction_t dir) const
        {
            if (to == nullptr || from == nullptr) {
                return;
            }

            auto pExit = from->exit(dir);

            if (pExit == nullptr || pExit->to() != to.get()) {
                from->create_exit(dir, to.get());
            }

            auto rDir = reverse_directions[dir];

            pExit = to->exit(rDir);

            if (pExit == nullptr || pExit->to() != from.get()) {
                to->create_exit(reverse_directions[dir], from.get());
            }
        }

        vector<vector<int>> dungeon::to_map() const
        {
            vector<vector<int>> value;

            for (int x = 0; x < xsize_; x++) {
                vector<int> inner;

                for (int y = 0; y < ysize_; y++) {
                    switch (cell(x, y)) {
                        case tileUnused:
                            inner.push_back(0);
                            break;
                        case tileDirtFloor:
                        case tileCorridor:
                        case tileDoor:
                        case tileUpStairs:
                        case tileDownStairs:
                            inner.push_back(0);
                            break;
                        case tileStoneWall:
                            inner.push_back(1);
                            break;
                        case tileDirtWall:
                            inner.push_back(2);
                            break;
                        case tileChest:
                            inner.push_back(3);
                            break;
                    }
                }

                value.push_back(inner);
            }

            return value;
        }

        string dungeon::to_string() const
        {
            std::ostringstream buf;

            buf << "\n";

            for (int y = 0; y < ysize_; y++) {
                for (int x = 0; x < xsize_; x++) {
                    switch (cell(x, y)) {
                        case tileUnused:
                            buf << '#';
                            break;
                        case tileDirtFloor:
                        case tileCorridor:
                        case tileDoor:
                        case tileUpStairs:
                        case tileDownStairs:
                            buf << ' ';
                            break;
                        case tileStoneWall:
                            buf << '@';
                            break;
                        case tileDirtWall:
                            buf << '&';
                            break;
                        case tileChest:
                            buf << '*';
                            break;
                    }
                }
                buf << "\n";
            }

            return buf.str();
        }

        area_ptr dungeon::to_area(const string &name) const
        {
            map<string, shared_ptr<location>> locations;

            area_ptr area = make_shared<game::area>();

            area->set_name(name);

            log::trace(format("building area {0}", area->name()));

            for (int y = 0; y < ysize_; y++) {
                for (int x = 0; x < xsize_; x++) {
                    switch (cell(x, y)) {
                        case tileDirtFloor:
                        case tileCorridor:
                        case tileDoor:
                        case tileUpStairs:
                        case tileDownStairs:
                            auto loc = add_location(area, x, y);
                            locations[format("{0}:{1}", x, y)] = loc;
                            break;
                    }
                }
            }

            for (int y = 0; y < ysize_; y++) {
                for (int x = 0; x < xsize_; x++) {
                    switch (cell(x, y)) {
                        case tileDirtFloor:
                        case tileCorridor:
                        case tileDoor:
                        case tileUpStairs:
                        case tileDownStairs:
                            auto from = locations[format("{0}:{1}", x, y)];
                            if (from != nullptr) {
                                if (y + 1 < ysize_) {
                                    auto to = locations[format("{0}:{1}", x, y + 1)];
                                    link_location(area, from, to, DIR_NORTH);
                                }
                                if (x + 1 < xsize_) {
                                    auto to = locations[format("{0}:{1}", x + 1, y)];
                                    link_location(area, from, to, DIR_EAST);
                                }
                                if (y > 0) {
                                    auto to = locations[format("{0}:{1}", x, y - 1)];
                                    link_location(area, from, to, DIR_SOUTH);
                                }
                                if (x > 0) {
                                    auto to = locations[format("{0}:{1}", x - 1, y)];
                                    link_location(area, from, to, DIR_WEST);
                                }
                            }
                            break;
                    }
                }
            }
            return area;
        }

        bool dungeon::generate(int inx, int iny, int inobj)
        {
            if (inobj < 1) {
                objects_ = 10;
            } else {
                objects_ = inobj;
            }

            // justera kartans storlek, om den ????r st????rre eller mindre ????n "gr????nserna"
            // adjust the size of the map, if it's smaller or bigger than the limits
            if (inx < 3) {
                xsize_ = 3;
            }
            // else if (inx > xmax_) xsize_ = xmax_;
            else {
                xsize_ = inx;
            }

            if (iny < 3) {
                ysize_ = 3;
            }
            // else if (iny > ymax_) ysize_ = ymax_;
            else {
                ysize_ = iny;
            }

            // redefine the map var, so it's adjusted to our new map size
            dungeon_map_ = new int[xsize_ * ysize_];

            // start with making the "standard stuff" on the map
            for (int y = 0; y < ysize_; y++) {
                for (int x = 0; x < xsize_; x++) {
                    // ie, making the borders of unwalkable walls
                    if (y == 0) {
                        set_cell(x, y, tileStoneWall);
                    } else if (y == ysize_ - 1) {
                        set_cell(x, y, tileStoneWall);
                    } else if (x == 0) {
                        set_cell(x, y, tileStoneWall);
                    } else if (x == xsize_ - 1) {
                        set_cell(x, y, tileStoneWall);
                    }

                    // and fill the rest with dirt
                    else {
                        set_cell(x, y, tileUnused);
                    }
                }
            }

            /*******************************************************************************
            And now the code of the random-map-generation-algorithm begins!
            *******************************************************************************/

            // start with making a room in the middle, which we can start building upon
            make_room(xsize_ / 2, ysize_ / 2, 8, 6, rand(0, 3));  // rand saken f????r att slumpa fram riktning p?? rummet

            // keep count of the number of "objects_" we've made
            int currentFeatures = 1;  //+1 for the first room we just made

            // then we sart the main loop
            for (int countingTries = 0; countingTries < 1000; countingTries++) {
                // check if we've reached our quota
                if (currentFeatures == objects_) {
                    break;
                }

                // start with a random wall
                int newx = 0;
                int xmod = 0;
                int newy = 0;
                int ymod = 0;
                int validTile = -1;
                // 1000 chances to find a suitable object (room or corridor)..
                //(yea, i know it's kinda ugly with a for-loop... -_-')
                for (int testing = 0; testing < 1000; testing++) {
                    newx = rand(1, xsize_ - 1);
                    newy = rand(1, ysize_ - 1);
                    validTile = -1;
                    // System.out.println("tempx: " + newx + "\ttempy: " + newy);
                    if (cell(newx, newy) == tileDirtWall || cell(newx, newy) == tileCorridor) {
                        // check if we can reach the place
                        if (cell(newx, newy + 1) == tileDirtFloor || cell(newx, newy + 1) == tileCorridor) {
                            validTile = 0;  //
                            xmod = 0;
                            ymod = -1;
                        } else if (cell(newx - 1, newy) == tileDirtFloor || cell(newx - 1, newy) == tileCorridor) {
                            validTile = 1;  //
                            xmod = +1;
                            ymod = 0;
                        } else if (cell(newx, newy - 1) == tileDirtFloor || cell(newx, newy - 1) == tileCorridor) {
                            validTile = 2;  //
                            xmod = 0;
                            ymod = +1;
                        } else if (cell(newx + 1, newy) == tileDirtFloor || cell(newx + 1, newy) == tileCorridor) {
                            validTile = 3;  //
                            xmod = -1;
                            ymod = 0;
                        }

                        // check that we haven't got another door nearby, so we won't get alot of openings besides
                        // each other
                        if (validTile > -1) {
                            if (cell(newx, newy + 1) == tileDoor) {  // north
                                validTile = -1;
                            } else if (cell(newx - 1, newy) == tileDoor) {  // east
                                validTile = -1;
                            } else if (cell(newx, newy - 1) == tileDoor) {  // south
                                validTile = -1;
                            } else if (cell(newx + 1, newy) == tileDoor) {  // west
                                validTile = -1;
                            }
                        }

                        // if we can, jump out of the loop and continue with the rest
                        if (validTile > -1) {
                            break;
                        }
                    }
                }
                if (validTile > -1) {
                    // choose what to build now at our newly found place, and at what direction
                    int feature = rand(0, 100);
                    if (feature <= chanceRoom_)  // a new room
                    {
                        if (make_room((newx + xmod), (newy + ymod), 8, 6, validTile)) {
                            currentFeatures++;  // add to our quota

                            // then we mark the wall opening with a door
                            set_cell(newx, newy, tileDoor);

                            // clean up infront of the door so we can reach it
                            set_cell((newx + xmod), (newy + ymod), tileDirtFloor);
                        }
                    } else if (feature >= chanceRoom_)  // new corridor
                    {
                        if (make_corridor((newx + xmod), (newy + ymod), 6, validTile)) {
                            // same thing here, add to the quota and a door
                            currentFeatures++;

                            set_cell(newx, newy, tileDoor);
                        }
                    }
                }
            }


            /*******************************************************************************
            All done with the building, let's finish this one off
            *******************************************************************************/

            // sprinkle out the bonusstuff (stairs, chests etc.) over the map
            int newx = 0;
            int newy = 0;
            int ways = 0;   // from how many directions we can reach the random spot from
            int state = 0;  // the state the loop is in, start with the stairs
            while (state != 10) {
                for (int testing = 0; testing < 1000; testing++) {
                    newx = rand(1, xsize_ - 1);
                    newy = rand(1, ysize_ - 2);  // cheap bugfix, pulls down newy to 0<y<24, from 0<y<25

                    // System.out.println("x: " + newx + "\ty: " + newy);
                    ways = 4;  // the lower the better

                    // check if we can reach the spot
                    if (cell(newx, newy + 1) == tileDirtFloor || cell(newx, newy + 1) == tileCorridor) {
                        // north
                        if (cell(newx, newy + 1) != tileDoor) {
                            ways--;
                        }
                    }
                    if (cell(newx - 1, newy) == tileDirtFloor || cell(newx - 1, newy) == tileCorridor) {
                        // east
                        if (cell(newx - 1, newy) != tileDoor) {
                            ways--;
                        }
                    }
                    if (cell(newx, newy - 1) == tileDirtFloor || cell(newx, newy - 1) == tileCorridor) {
                        // south
                        if (cell(newx, newy - 1) != tileDoor) {
                            ways--;
                        }
                    }
                    if (cell(newx + 1, newy) == tileDirtFloor || cell(newx + 1, newy) == tileCorridor) {
                        // west
                        if (cell(newx + 1, newy) != tileDoor) {
                            ways--;
                        }
                    }

                    if (state == 0) {
                        if (ways == 0) {
                            // we're in state 0, let's place a "upstairs" thing
                            set_cell(newx, newy, tileUpStairs);
                            state = 1;
                            break;
                        }
                    } else if (state == 1) {
                        if (ways == 0) {
                            // state 1, place a "downstairs"
                            set_cell(newx, newy, tileDownStairs);
                            state = 10;
                            break;
                        }
                    }
                }
            }

            return true;
        }

        dungeon::dungeon(int chanceRoom) : xsize_(0), ysize_(0), objects_(0), chanceRoom_(chanceRoom)
        {
        }
    }
}
