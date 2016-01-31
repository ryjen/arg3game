#ifndef ARG3_GAME_ENTITY_H
#define ARG3_GAME_ENTITY_H

#ifndef SWIG
#include <cstdint>
#include <memory>
#include <string>
#endif

namespace arg3
{
    namespace game
    {
        class entity
        {
           public:
            virtual std::string id() const = 0;

            bool operator==(const entity &e) const;
            bool operator!=(const entity &e) const;
        };
    }
}

#endif
