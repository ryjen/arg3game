#ifndef ARG3_GAME_WORLD_H
#define ARG3_GAME_WORLD_H

#include "db.h"
#include <list>
#include "typedef.h"

namespace arg3
{
    namespace game
    {
        class area;

        class world : public record<world>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "worlds";
            constexpr static const char *const COL_PORT = "port";
            constexpr static const char *const COL_NAME = "name";
            constexpr static const char *const COL_WS_PORT = "websocket_port";
            constexpr static const char *const COL_DB_NAME = "db_name";
#endif
            typedef list<area_ptr>::const_iterator const_iterator;
            typedef list<area_ptr>::iterator iterator;

            world();
            ~world();
            world(const world &world);
            world(world &&world);
            world &operator=(const world &world);
            world &operator=(world &&world);

            int port() const;
            void set_port(int value);

            int websocket_port() const;
            void set_websocket_port(int value);

            string db_name() const;
            void set_db_name(const string &value);

            string name() const;
            void set_name(const string &value);

            static world_ptr create_default();

            void from_storage(const storage &obj);
            void to_storage(storage_builder &obj) const;

            bool save();

            void add(area_ptr area);

            const_iterator begin() const;
            const_iterator end() const;
            iterator begin();
            iterator end();

            template <typename T>
            location_ptr find_location(const string &name, const T &value)
            {
                for (auto area : areas_) {
                    auto loc = area->find_location(name, value);

                    if (loc != nullptr) {
                        return loc;
                    }
                }
                return nullptr;
            }

           private:
            list<area_ptr> areas_;
        };
    }
}

#endif
