#include "location.h"
#include "area.h"
#include "exit.h"
#include "util.h"
#include <arg3str/util.h>

namespace arg3
{
    namespace game
    {
        location::location() : area_(nullptr), exits_({{0}})
        {
        }

        location::location(const location &loc)
            : record(loc), characters_(loc.characters_), objects_(loc.objects_), area_(loc.area_), exits_(loc.exits_)
        {
        }

        location &location::operator=(const location &loc)
        {
            record::operator=(loc);
            characters_ = loc.characters_;
            objects_ = loc.objects_;
            area_ = loc.area_;
            exits_ = loc.exits_;
            return *this;
        }

        location::location(location &&loc)
            : record(loc), characters_(std::move(loc.characters_)), objects_(std::move(loc.objects_)), area_(loc.area_), exits_(loc.exits_)
        {
            loc.area_ = nullptr;
        }

        location::~location()
        {
            if (area_ != nullptr) {
                area_->remove(this);
            }
        }

        location &location::operator=(location &&loc)
        {
            record::operator=(std::move(loc));
            characters_ = std::move(loc.characters_);
            objects_ = std::move(loc.objects_);
            exits_ = std::move(loc.exits_);
            area_ = loc.area_;
            loc.area_ = nullptr;
            return *this;
        }

        const char *location::swig_type_name() const
        {
            return "arg3::game::location *";
        }

        location &location::add(character_ptr ch)
        {
            characters_.push_back(ch);
            ch->set_location(this);
            return *this;
        }

        location &location::remove(character_ptr ch)
        {
            characters_.remove(ch);
            ch->set_location(nullptr);
            return *this;
        }

        location &location::add(object_ptr obj)
        {
            objects_.push_back(obj);
            obj->set_location(this);
            return *this;
        }

        location &location::remove(object_ptr obj)
        {
            objects_.remove(obj);
            obj->set_location(nullptr);
            return *this;
        }

        string location::name() const
        {
            return get<string>(COL_NAME);
        }

        void location::set_name(const string &value)
        {
            set(COL_NAME, value);
        }

        game::area *location::area() const
        {
            return area_;
        }
        void location::set_area(game::area *area)
        {
            area_ = area;
        }

        bool location::is_valid() const
        {
            return area_ && area_->is_saved();
        }

        bool location::save()
        {
            bool rval = record::save();

            for (auto &e : exits_) {
                if (e != nullptr && e->is_valid()) {
                    rval = e->save() && rval;
                }
            }

            return rval;
        }

        exit_ptr location::exit(direction_t dir) const
        {
            return exits_[dir];
        }

        location &location::add(exit_ptr e)
        {
            assert(e != nullptr);
            exits_[e->direction()] = e;
            e->set_from(this);
            return *this;
        }

        void location::create_exit(direction_t dir, location *to)
        {
            exit_ptr e = make_shared<game::exit>();
            e->set_to(to);
            e->set_from(this);
            e->set_direction(dir);

            if (exits_[dir] != nullptr) {
                remove_exit(dir);
            }
            exits_[dir] = e;
        }

        void location::remove_exit(direction_t dir)
        {
            if (exits_[dir] == nullptr) {
                return;
            }

            exit_ptr e = exits_[dir];

            e->de1ete();

            exits_[dir] = nullptr;
        }

        void location::remove_exit(exit_ptr e)
        {
            for (auto i = 0; i < exits_.size(); i++) {
                if (exits_[i] == e) {
                    exits_[i] = nullptr;
                    return;
                }
            }
        }

        location &location::operator<<(const std::string &value)
        {
            for (auto &ch : characters_) {
                ch->write(value);
            }
            return *this;
        }

        location &location::write(const std::string &value)
        {
            for (auto &ch : characters_) {
                ch->write(value);
            }
            return *this;
        }
        location &location::writeln()
        {
            for (auto &ch : characters_) {
                ch->writeln();
            }
            return *this;
        }
        location &location::writeln(const std::string &value)
        {
            for (auto &ch : characters_) {
                ch->writeln(value);
            }
            return *this;
        }
        location &location::write(void *buf, size_t sz)
        {
            for (auto &ch : characters_) {
                ch->write(buf, sz);
            }
            return *this;
        }

        void location::to_storage(storage_builder &obj) const
        {
            obj << COL_NAME << name();

            area()->store_reference(obj);
        }

        void location::from_storage(const storage &obj)
        {
            set_name(obj[COL_NAME].str());

            auto exits = find_all_by_ref<game::exit>(exit::COL_FROM_LOCATION);

            for (auto &e : exits) {
                add(e);
            }
        }
    }
}