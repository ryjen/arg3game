#include "npc.h"

namespace arg3
{
    namespace game
    {
        npc::npc()
        {
        }

        npc::npc(const npc &other) : character(other), record<npc>(other)
        {
        }

        npc::~npc()
        {
        }

        npc::npc(npc &&other) : character(other), record<npc>(other)
        {
        }

        npc &npc::operator=(npc &&other)
        {
            character::operator=(other);
            record<npc>::operator=(other);
            return *this;
        }
        const char *npc::swig_type_name() const
        {
            return "arg3::game::npc *";
        }

        npc &npc::operator=(const npc &other)
        {
            character::operator=(other);
            record<npc>::operator=(other);
            return *this;
        }
        npc &npc::writeln()
        {
            return *this;
        }
        npc &npc::writeln(const std::string &value)
        {
            return *this;
        }

        npc &npc::write(const std::string &value)
        {
            return *this;
        }
        npc &npc::write(void *buf, size_t sz)
        {
            return *this;
        }

        npc &npc::operator<<(const std::string &value)
        {
            return *this;
        }

        void npc::from_storage(const storage &obj)
        {
        }

        void npc::to_storage(storage_builder &obj) const
        {
        }
    }
}
