#ifndef ARG3_GAME_AREA_H
#define ARG3_GAME_AREA_H

#include "writable.h"
#include "db.h"
#include <list>
#include "location.h"
#include "sector.h"
#include "typedef.h"

namespace arg3
{
    namespace game
    {
        class area : public writable, public record<area>
        {
           public:
#ifndef SWIG
            constexpr static const char *const TABLE_NAME = "areas";
            constexpr static const char *const COL_NAME = "name";
#endif
            typedef std::list<location_ptr>::const_iterator const_iterator;
            typedef std::list<location_ptr>::iterator iterator;
            area();
            area(const area &area);
            virtual ~area();
            area &operator=(const area &area);

            area(area &&area);
            area &operator=(area &&area);

            area &add(location_ptr location);
            area &remove(location *location);

            area &write(const std::string &value);
            area &writeln();
            area &writeln(const std::string &value);
            area &write(void *buf, size_t sz);
            area &operator<<(const std::string &value);

            bool save();

            string name() const;
            void set_name(const string &value);

            void set_world(arg3::game::world *world);
            arg3::game::world *world() const;

            const_iterator begin() const;
            const_iterator end() const;

            iterator begin();
            iterator end();

            void to_storage(storage_builder &obj) const;
            void from_storage(const storage &obj);

            bool is_valid() const;

            vector<vector<sector_t>> to_tilemap() const;

            template <typename T>
            shared_ptr<location> find_location(const string &field, const T &value)
            {
                for (auto &loc : *this) {
                    if (loc->get<T>(field) == value) {
                        return loc;
                    }
                }
                return nullptr;
            }

           private:
            void copy(const area &other);
            void move(area &&other);
            std::list<location_ptr> locations_;
            arg3::game::world *world_;
        };
    }
}

#endif
