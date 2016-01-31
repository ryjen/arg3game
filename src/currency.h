#ifndef ARG3_GAME_CURRENCY_H
#define ARG3_GAME_CURRENCY_H

#include <string>

namespace arg3
{
    namespace game
    {
        class currency
        {
           public:
            typedef unsigned long value_type;

            currency(const value_type &gold, const value_type &silver);
            currency(const value_type &silver);
            currency(const currency &other);
            currency();

            currency &operator=(const currency &rhs);
            operator value_type() const;

            bool operator==(const currency &rhs) const;
            bool operator!=(const currency &rhs) const;
            bool operator>(const currency &rhs) const;
            bool operator<(const currency &rhs) const;
            bool operator>=(const currency &rhs) const;
            bool operator<=(const currency &rhs) const;

            currency &operator++();
            currency &operator--();
            currency operator++(int i) const;
            currency operator--(int i) const;

            bool operator!() const;

            currency operator*(const currency &rhs);
            currency operator+(const currency &rhs);
            currency operator-(const currency &rhs);
            currency operator/(const currency &rhs);
            currency operator%(const currency &rhs);

            currency &operator*=(const currency &rhs);
            currency &operator+=(const currency &rhs);
            currency &operator-=(const currency &rhs);
            currency &operator/=(const currency &rhs);
            currency &operator%=(const currency &rhs);

            value_type value() const;
            value_type copper() const;
            value_type silver() const;
            void silver(const value_type &value);
            value_type gold() const;
            void gold(const value_type &value);
            value_type platinum() const;

            std::string to_string() const;
            std::string to_string(const std::string &fmt) const;

            currency &add(const currency &value);
            currency &subtract(const currency &value);
            currency &multiply(const currency &value);
            currency &divide(const currency &value);
            currency &mod(const currency &value);

           private:
            currency &normalize();
            value_type gold_, silver_;
        };

        currency operator"" _C(unsigned long long);
    }
}

#endif
