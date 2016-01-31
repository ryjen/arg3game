#include "object.h"
#include "character.h"
#include "location.h"

namespace arg3
{
    namespace game
    {
        object::object() : carriedBy_(nullptr), location_(nullptr)
        {
        }

        object::object(const object &obj) : record(obj), carriedBy_(obj.carriedBy_), location_(obj.location_)
        {
        }

        object::object(object &&obj) : record(obj), carriedBy_(std::move(obj.carriedBy_)), location_(std::move(obj.location_))
        {
        }

        object::~object()
        {
        }

        object &object::operator=(const object &obj)
        {
            record::operator=(obj);
            carriedBy_ = obj.carriedBy_;
            location_ = obj.location_;
            return *this;
        }

        object &object::operator=(object &&obj)
        {
            record::operator=(obj);
            carriedBy_ = obj.carriedBy_;
            location_ = obj.location_;
            obj.carriedBy_ = nullptr;
            obj.location_ = nullptr;
            return *this;
        }

        game::location *object::location() const
        {
            return location_;
        }

        void object::set_location(game::location *loc)
        {
            location_ = loc;
        }

        void object::to_storage(storage_builder &obj) const
        {
        }

        void object::from_storage(const storage &obj)
        {
        }

        const char *object::swig_type_name() const
        {
            return "arg3::game::object *";
        }

        object &object::write(const std::string &value)
        {
            if (carriedBy_ != nullptr) carriedBy_->write(value);

            return *this;
        }
        object &object::writeln()
        {
            if (carriedBy_ != nullptr) carriedBy_->writeln();
            return *this;
        }
        object &object::writeln(const std::string &value)
        {
            if (carriedBy_ != nullptr) carriedBy_->writeln(value);

            return *this;
        }
        object &object::write(void *buf, size_t sz)
        {
            if (carriedBy_ != nullptr) carriedBy_->write(buf, sz);

            return *this;
        }
    }
}