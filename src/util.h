#ifndef ARG3_GAME_UTIL_H
#define ARG3_GAME_UTIL_H

#include <functional>
#include <random>
#include <arg3format/format.h>

namespace arg3
{
    namespace game
    {
        extern std::default_random_engine randomEngine;

        template <class I>
        I rand(I a, I b)
        {
            std::uniform_int_distribution<I> distribution(a, b);

            return distribution(randomEngine);
        }

        template <class I>
        I rand(I n)
        {
            std::uniform_int_distribution<I> distribution(0, n);

            return distribution(randomEngine);
        }


        // counts the number of lines in a string
        int count_lines(const string &);

        // function object to determine if one char is less than another char (case insensitive)
        struct no_case_less_char : public std::binary_function<char, char, bool> {
            bool operator()(char x, char y) const
            {
                return toupper(static_cast<unsigned char>(x)) < toupper(static_cast<unsigned char>(y));
            }
        };

        // function object to determine if one string is less than another string (case insensitive)
        struct no_case_less : public std::binary_function<string, string, bool> {
            bool operator()(const string &x, const string &y) const
            {
                return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end(), no_case_less_char());
            }
        };
        typedef function<bool(const string &a, const string &b, bool caseSensitive)> str_comparer;

        // find the position a string is contained in another (case insensitive)
        string::const_iterator stristr(const string &, const string &);
        // given a start and end point in a string, put the contents into another string untill a new line is found
        void get_line(string::const_iterator &, const string::const_iterator &, string &);
    }
}

#endif
