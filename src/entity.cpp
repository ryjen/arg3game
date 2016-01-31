#include "entity.h"

namespace arg3
{
    namespace game
    {
        bool entity::operator==(const entity &e) const
        {
            return id() == e.id();
        }

        bool entity::operator!=(const entity &e) const
        {
            return id() != e.id();
        }
    }
}