#include "util.h"

namespace arg3
{
    namespace game
    {
        std::default_random_engine randomEngine(time(NULL));

        string::const_iterator stristr(const string &String, const string &Pattern)
        {
            // string::const_iterator pptr, sptr;

            for (auto start = String.cbegin(); start != String.cend(); ++start) {
                /* find start of pattern in string */
                for (; ((*start != 0) && (toupper(*start) != toupper(*Pattern.begin()))); start++)
                    ;
                if (start == String.end()) {
                    return start;
                }

                auto pptr = Pattern.cbegin();
                auto sptr = start;

                while (toupper(*sptr) == toupper(*pptr)) {
                    sptr++;
                    pptr++;

                    /* if end of pattern then pattern was found */

                    if (String.cend() == pptr) {
                        return start;
                    }
                }
            }
            return String.cend();
        }

        void get_line(string::const_iterator &pstr, const string::const_iterator &end, string &buf)
        {
            buf.clear();

            while (pstr != end) {
                if (*pstr == '\n') {
                    break;
                }

                buf += *pstr++;
            }

            if (pstr != end) {
                if (*(++pstr) == '\r') {
                    pstr++;
                }
            }
        }

        int count_lines(const string &pstr)
        {
            int count = 0;
            auto c = pstr.cbegin();

            while (c != pstr.cend()) {
                if (*c == '\n') {
                    count++;
                }

                if (*(++c) == '\r') {
                    c++;
                }
            }

            return count;
        }
    }
}