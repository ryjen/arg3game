
#ifndef ARG3_GAME_TERM_COLOR_H
#define ARG3_GAME_TERM_COLOR_H

#include <string>

namespace arg3
{
    namespace game
    {
        enum class alignment { LEFT, CENTER, RIGHT, INDENT };

        class color
        {
           private:
            uint8_t attr;
            uint8_t value;

           public:
            static const uint8_t CODE = '~';

            static const uint8_t DARK = 30;
            static const uint8_t RED = 31;
            static const uint8_t GREEN = 32;
            static const uint8_t YELLOW = 33;
            static const uint8_t BLUE = 34;
            static const uint8_t MAGENTA = 35;
            static const uint8_t CYAN = 36;
            static const uint8_t WHITE = 37;

            /*
                        // bold
                        constexpr static const color D = color(DARK, BOLD);
                        constexpr static const color R = color(RED, BOLD);
                        constexpr static const color G = color(GREEN, BOLD);
                        constexpr static const color Y = color(YELLOW, BOLD);
                        constexpr static const color B = color(BLUE, BOLD);
                        constexpr static const color M = color(MAGENTA, BOLD);
                        constexpr static const color C = color(CYAN, BOLD);
                        constexpr static const color W = color(WHITE, BOLD);

                        // normal
                        constexpr static const color d = color(DARK, NORMAL);
                        constexpr static const color r = color(RED, NORMAL);
                        constexpr static const color g = color(GREEN, NORMAL);
                        constexpr static const color y = color(YELLOW, NORMAL);
                        constexpr static const color b = color(BLUE, NORMAL);
                        constexpr static const color m = color(MAGENTA, NORMAL);
                        constexpr static const color c = color(CYAN, NORMAL);
                        constexpr static const color w = color(WHITE, NORMAL);
            */
            static const uint8_t BG_MOD = 10;

            static const uint8_t BOLD = 1;
            static const uint8_t NORMAL = 0;
            static const uint8_t IGNORE = 255;
            static const uint8_t BLINK = 5;

            color(uint8_t value, uint8_t attr = NORMAL);

            operator std::string() const;
            std::string to_string() const;
            const unsigned char *convert(const unsigned char *);

            static bool valid_attr(uint8_t);
            static bool valid_color(uint8_t);

            static std::string strip(const std::string &);

            static int count_codes(const std::string &);

            static int strlen(const std::string &);

            static int find(const std::string &, size_t);

            // a string repeated a number of times
            static std::string fill(const std::string &, size_t);
            // aligns a string
            static std::string align(const std::string &, int, std::string = " ", alignment = alignment::CENTER, const std::string & = std::string());
        };
    }
}

#endif  //  #ifndef COLOR_H
