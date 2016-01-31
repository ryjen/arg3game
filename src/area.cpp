#include "area.h"
#include "location.h"
#include "world.h"
#include "exit.h"

namespace arg3
{
    namespace game
    {
        area::area() : world_(nullptr)
        {
        }

        area::area(const area &area) : record(area)
        {
            copy(area);
        }

        area::area(area &&area) : record(area)
        {
            move(std::move(area));
            area.world_ = nullptr;
        }

        area::~area()
        {
        }

        void area::copy(const area &area)
        {
            locations_ = area.locations_;
            world_ = area.world_;
        }

        void area::move(area &&area)
        {
            locations_ = std::move(area.locations_);
            world_ = area.world_;
            area.world_ = nullptr;
        }

        area &area::operator=(const area &area)
        {
            entity::operator=(area);
            record::operator=(area);
            copy(area);
            return *this;
        }
        area &area::operator=(area &&area)
        {
            entity::operator=(std::move(area));
            record::operator=(std::move(area));
            move(std::move(area));
            return *this;
        }

        bool area::is_valid() const
        {
            return world_ != NULL && world_->is_saved();
        }

        bool area::save()
        {
            bool rval = record::save();

            if (!rval) {
                return false;
            }

            for (auto &loc : locations_) {
                if (loc->is_valid()) {
                    rval = loc->save() && rval;
                }
            }

            return rval;
        }

        string area::name() const
        {
            return get<string>(COL_NAME);
        }

        void area::set_name(const string &value)
        {
            set(COL_NAME, value);
        }

        area::const_iterator area::begin() const
        {
            return locations_.begin();
        }

        area::const_iterator area::end() const
        {
            return locations_.end();
        }

        area::iterator area::begin()
        {
            return locations_.begin();
        }

        area::iterator area::end()
        {
            return locations_.end();
        }

        area &area::add(location_ptr loc)
        {
            locations_.push_back(loc);

            loc->set_area(this);

            return *this;
        }

        area &area::remove(location *loc)
        {
            remove_if(locations_.begin(), locations_.end(), [&](const location_ptr &ptr) { return ptr.get() == loc; });

            loc->set_area(nullptr);

            return *this;
        }

        world *area::world() const
        {
            return world_;
        }

        void area::set_world(game::world *world)
        {
            world_ = world;
        }

        area &area::operator<<(const std::string &value)
        {
            for (auto &loc : locations_) {
                loc->write(value);
            }
            return *this;
        }

        area &area::write(const std::string &value)
        {
            for (auto &loc : locations_) {
                loc->write(value);
            }
            return *this;
        }
        area &area::writeln()
        {
            for (auto &loc : locations_) {
                loc->writeln();
            }
            return *this;
        }
        area &area::writeln(const std::string &value)
        {
            for (auto &loc : locations_) {
                loc->writeln(value);
            }
            return *this;
        }
        area &area::write(void *buf, size_t sz)
        {
            for (auto &loc : locations_) {
                loc->write(buf, sz);
            }
            return *this;
        }

        void area::from_storage(const storage &obj)
        {
            set(COL_NAME, obj[COL_NAME].str());

            log::info(format("Loaded area {0}", name()));

            auto locations = find_all_by_ref<location>();

            for (auto &loc : locations) {
                loc->set_area(this);

                add(loc);
            }
        }

        void area::to_storage(storage_builder &obj) const
        {
            obj << COL_NAME << name();

            world()->store_reference(obj);
        }

        vector<vector<sector_t>> area::to_tilemap() const
        {
            vector<vector<sector_t>> value;

            int dir_count[DIR_MAX] = {0};

            auto loc = locations_.begin();

            while (loc != locations_.end()) {
                for (int i = DIR_START; i < DIR_MAX; i++) {
                    direction_t dir = static_cast<direction_t>(i);

                    auto ex = (*loc)->exit(dir);

                    if (ex != nullptr && ex->to()->exit(reverse_directions[dir])) {
                        dir_count[dir]++;
                    }
                }
            }

            int map_height = dir_count[DIR_NORTH] + dir_count[DIR_SOUTH];

            // TODO: implement

            return value;
        }
    }
}
