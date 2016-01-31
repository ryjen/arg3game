#ifndef ARG3_GAME_WRITABLE_H
#define ARG3_GAME_WRITABLE_H

#include <string>

#ifdef WIN32
#define __attribute__(a)
#endif
namespace arg3
{
    namespace game
    {
        class writable
        {
           public:
            virtual writable &write(const std::string &value) = 0;
            virtual writable &write(void *buf, size_t buf_size) = 0;
            virtual writable &writeln(const std::string &value) = 0;
            virtual writable &writeln() = 0;
            virtual writable &operator<<(const std::string &value) = 0;

           protected:
            constexpr static const char *const NEWLINE = "\r\n";
        };
    }
}
#endif
