#ifndef ARG3_GAME_EXCEPTION_H
#define ARG3_GAME_EXCEPTION_H

#include <exception>
#include <string>

namespace arg3
{
    namespace game
    {
        class game_exception : public std::exception
        {
           public:
            game_exception() throw()
            {
            }
            game_exception(const std::string &logMessage) throw() : logMessage_(logMessage)
            {
            }
            game_exception(const game_exception &other) throw() : logMessage_(other.logMessage_)
            {
            }
            game_exception(game_exception &&other) throw() : logMessage_(std::move(other.logMessage_))
            {
            }
            virtual ~game_exception() throw()
            {
            }

            game_exception &operator=(const game_exception &other) throw()
            {
                if (this != &other) {
                    logMessage_ = other.logMessage_;
                }
                return *this;
            }

            game_exception &operator=(game_exception &&other) throw()
            {
                if (this != &other) {
                    logMessage_ = std::move(other.logMessage_);
                }
                return *this;
            }

            const char *what() const throw()
            {
                return logMessage_.c_str();
            }

           private:
            std::string logMessage_;
        };

        class control_exception : public game_exception
        {
           public:
            control_exception() throw()
            {
            }
            control_exception(const std::string &logMessage) throw() : game_exception(logMessage)
            {
            }
        };

        class shutdown_exception : public control_exception
        {
           public:
            shutdown_exception() throw()
            {
            }
            shutdown_exception(const std::string &logMessage) throw() : control_exception(logMessage)
            {
            }
        };
    }
}

#endif
