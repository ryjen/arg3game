#include "area.h"
#include "world.h"
#include "dungeon.h"
#include "exit.h"

namespace arg3
{
    namespace game
    {
        world::world()
        {
        }

        world::~world()
        {
        }

        world::world(const world &world) : record(world)
        {
        }

        world::world(world &&world) : record(std::move(world)), areas_(std::move(world.areas_))
        {
        }

        world &world::operator=(const world &world)
        {
            record::operator=(world);
            areas_ = world.areas_;
            return *this;
        }
        world &world::operator=(world &&world)
        {
            record::operator=(world);
            areas_ = world.areas_;
            return *this;
        }

        world::const_iterator world::begin() const
        {
            return areas_.begin();
        }

        world::const_iterator world::end() const
        {
            return areas_.end();
        }

        world::iterator world::begin()
        {
            return areas_.begin();
        }

        world::iterator world::end()
        {
            return areas_.end();
        }

        void world::from_storage(const storage &obj)
        {
            set(COL_PORT, obj[COL_PORT].Int());
            set(COL_WS_PORT, obj[COL_WS_PORT].Int());
            set(COL_DB_NAME, obj[COL_DB_NAME].str());
            set(COL_NAME, obj[COL_NAME].str());

            log::trace(format("Loaded world {0}", name()));

            auto areas = find_all_by_ref<area>();

            for (auto &area : areas) {
                area->set_world(this);

                add(area);

                for (auto &loc : *area) {
                    for (int i = DIR_START; i < DIR_MAX; i++) {
                        auto e = loc->exit(static_cast<direction_t>(i));

                        if (e == nullptr) {
                            continue;
                        }

                        location *to = e->to();

                        if (to == NULL) {
                            continue;
                        }

                        to->create_exit(reverse_directions[e->direction()], loc.get());
                    }
                }
            }
        }

        void world::to_storage(storage_builder &obj) const
        {
            obj << COL_NAME << name();
            obj << COL_PORT << port();
            obj << COL_WS_PORT << websocket_port();
            obj << COL_DB_NAME << db_name();
        }

        int world::port() const
        {
            return get<int>(COL_PORT);
        }

        void world::set_port(int value)
        {
            set(COL_PORT, value);
        }

        int world::websocket_port() const
        {
            return get<int>(COL_WS_PORT);
        }

        void world::set_websocket_port(int value)
        {
            set(COL_WS_PORT, value);
        }

        string world::db_name() const
        {
            return get<string>(COL_DB_NAME);
        }

        void world::set_db_name(const string &value)
        {
            set(COL_DB_NAME, value);
        }

        string world::name() const
        {
            return get<string>(COL_NAME);
        }

        void world::set_name(const string &value)
        {
            set(COL_NAME, value);
        }

        bool world::save()
        {
            bool rval = record::save();

            for (auto &area : areas_) {
                area->save();
            }

            return rval;
        }

        void world::add(shared_ptr<area> area)
        {
            areas_.push_back(area);

            area->set_world(this);
        }

        shared_ptr<world> world::create_default()
        {
            log::info("creating default world");

            shared_ptr<world> worldPtr = std::make_shared<world>();

            worldPtr->set_port(3778);
            worldPtr->set_name("Arthea");
            worldPtr->set_db_name("arg3game");
            worldPtr->set_websocket_port(3779);

            worldPtr->save();

            dungeon d;

            if (d.generate(80, 25, 100)) {
                auto area = d.to_area("Limbo");

                area->set_world(worldPtr.get());

                worldPtr->add(area);

                if (area->save()) {
                    for (auto &l : *area) {
                        if (l->save()) {
                        }
                    }

                    for (auto &l : *area) {
                        for (int i = DIR_START; i < DIR_MAX; i++) {
                            auto e = l->exit(static_cast<direction_t>(i));
                            if (e != nullptr) {
                                e->save();
                            }
                        }
                    }
                }
            }


            return worldPtr;
        }
    }
}