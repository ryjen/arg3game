#include "color.h"
#include <assert.h>
#include "util.h"

using namespace std;

namespace arg3
{
    namespace game
    {
        color::color(uint8_t val, uint8_t att) : attr(att), value(val)
        {
        }

        string color::strip(const string &str)
        {
            string buf;

            for (auto pstr = str.cbegin(); pstr != str.cend(); ++pstr) {
                if (*pstr != color::CODE) {
                    buf += *pstr;
                    continue;
                }

                if (++pstr == str.cend()) {
                    break;
                }

                if (*pstr == '!') {
                    if (++pstr == str.cend()) {
                        break;
                    }
                }
            }

            return buf;
        }


        int color::count_codes(const std::string &str)
        {
            int count = 0;
            for (auto pstr = str.cbegin(); pstr != str.cend(); ++pstr) {
                if (*pstr != color::CODE) {
                    continue;
                }
                count++;

                if (++pstr == str.cend()) {
                    break;
                }

                if (*pstr == '!') {
                    count++;
                    if (++pstr == str.cend()) {
                        break;
                    }
                }
            }
            return count;
        }

        int color::strlen(const std::string &str)
        {
            int count = 0;
            for (auto pstr = str.cbegin(); pstr != str.cend(); ++pstr) {
                if (*pstr != color::CODE) {
                    count++;
                    continue;
                }

                if (++pstr == str.cend()) {
                    break;
                }

                if (*pstr == '!') {
                    if (++pstr == str.cend()) {
                        break;
                    }
                }
            }
            return count;
        }


        bool color::valid_attr(uint8_t a)
        {
            return (a == BOLD) || (a == NORMAL) || (a == BLINK);
        }

        bool color::valid_color(uint8_t c)
        {
            return (c >= DARK && c <= WHITE) || (c >= (DARK + BG_MOD) && c <= (WHITE + BG_MOD));
        }

        color::operator string() const
        {
            return to_string();
        }

        string color::to_string() const
        {
            string buf("\x1b[0");

            if (valid_attr(this->attr)) {
                buf += ";";
                buf += std::to_string(this->attr);
                // len += sprintf(&buf[index][len], "%d;", (int16_t) this->attr);
            }

            if (valid_color(this->value)) {
                buf += ";";
                buf += std::to_string(this->value);
                // sprintf(&buf[index][len], "%d", (int16_t) this->value);
            }

            buf += "m";

            return buf;
        }

        const unsigned char *color::convert(const unsigned char *pstr)
        {
            assert(pstr && *pstr == color::CODE);

            pstr++;

            bool bg = *pstr == '!';

            if (bg) {
                pstr++;
            }
            if (*pstr == color::CODE) {
                return pstr;
            }

            this->value = bg ? BG_MOD : NORMAL;

            if (islower(*pstr)) {
                this->attr = NORMAL;
            } else if (isupper(*pstr)) {
                this->attr = BOLD;
            } else {
                this->attr = IGNORE;
            }

            // add to the color value so the background mod will be
            // taken into account
            switch (toupper(*pstr)) {
                case '\0':
                    break;
                case 'X':
                    this->attr = NORMAL;
                    this->value = NORMAL;
                    break;
                case '?':
                    this->attr = game::rand(NORMAL, BOLD);
                    this->value += game::rand(RED, WHITE);
                    break;
                case 'B':
                    this->value += BLUE;
                    break;
                case 'G':
                    this->value += GREEN;
                    break;
                case 'R':
                    this->value += RED;
                    break;
                case 'Y':
                    this->value += YELLOW;
                    break;
                case 'M':
                    this->value += MAGENTA;
                    break;
                case 'W':
                    this->value += WHITE;
                    break;
                case 'C':
                    this->value += CYAN;
                    break;
                case 'D':
                    this->value += DARK;
                    break;
            }

            return pstr;
        }


        int color::find(const string &str, size_t width)
        {
            size_t i = 0, count = 0;

            for (i = 0; i < str.length(); i++) {
                if (str[i] != color::CODE) {
                    if (++count >= width) {
                        return i + 1;
                    }
                    continue;
                }

                if (str[++i] == '!') {
                    i++;
                }
            }
            return i;
        }


        static string fill_str_len(const string &src, int len)
        {
            int sz, cz, c, mod, count;
            string result;

            if (src.length() == 0 || len <= 0) {
                return result;
            }

            cz = color::strlen(src);
            mod = len % cz;
            len /= cz;

            sz = src.length();
            count = 0;

            for (c = 0; c < len; c++) {
                result += src;
            }

            for (c = 0; c < sz && count < mod; c++) {
                if (src[c] == color::CODE) {
                    result += src[c++];

                    if (src[c] == '!') {
                        result += src[c++];
                    }

                    result += src[c];
                } else {
                    result += src[c];
                    count++;
                }
            }

            return result;
        }

        string color::align(const string &str, int width, string fill, alignment align, const string &color)
        {
            int nCount, cnt, sz;

            string result;

            if (fill.length() == 0) {
                fill = " ";
            }

            sz = color::strlen(str);
            nCount = std::min(sz, width);

            if (!color.empty()) {
                result.append(color);
            }

            switch (align) {
                case alignment::RIGHT:
                    cnt = (width - ++nCount);
                    result.append(fill_str_len(fill, width - nCount));
                    break;

                case alignment::CENTER:
                    nCount = (width - nCount) / 2;
                    cnt = nCount;
                    result.append(fill_str_len(fill, nCount));
                    break;
                case alignment::LEFT:
                    nCount = 8;
                    cnt = nCount;
                    result.append(fill_str_len(fill, nCount));
                    break;
                default:
                    cnt = 0;
                    break;
            }

            int pos = find(str, width);

            result.append(str.substr(0, pos));

            cnt = std::min(cnt + sz, width);

            result.append(fill_str_len(fill, width - cnt));

            if (color.length()) {
                result.append("~x");
            }

            return result;
        }

        string color::fill(const string &fill, size_t len)
        {
            string tmp(fill);

            if (tmp.empty()) {
                tmp = "-";
            }

            return fill_str_len(tmp, len);
        }
    }
}
