#ifndef ARG3_GAME_NPC_H
#define ARG3_GAME_NPC_H

#include "character.h"
namespace arg3
{
    namespace game
    {
        class npc : public character, public record<npc>
        {
           public:
            npc();
            npc(const npc &other);
            virtual ~npc();
#ifndef SWIG
            npc(npc &&other);
            npc &operator=(npc &&other);
            const char *swig_type_name() const;
#endif
            npc &operator=(const npc &other);
            npc &writeln();
            npc &writeln(const std::string &value);
            npc &write(const std::string &value);
            npc &write(void *buf, size_t sz);
            npc &operator<<(const std::string &value);

            void to_storage(storage_builder &obj) const;
            void from_storage(const storage &obj);
        };
    }
}

#endif
