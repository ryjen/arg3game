#include "currency.h"
#include <arg3format/format.h>

namespace arg3
{
    namespace game
    {
        currency operator"" _C(unsigned long long value)
        {
            return currency(value);
        }

        currency::currency(const value_type &gold, const value_type &silver) : gold_(gold), silver_(silver)
        {
            normalize();
        }
        currency::currency(const value_type &silver) : gold_(silver / 100), silver_(silver % 100)
        {
            normalize();
        }
        currency::currency(const currency &other) : gold_(other.gold_), silver_(other.silver_)
        {
            normalize();
        }

        currency::currency() : gold_(0), silver_(0)
        {
        }

        currency &currency::operator=(const currency &rhs)
        {
            if (this != &rhs) {
                gold_ = rhs.gold_;
                silver_ = rhs.silver_;
                normalize();
            }
            return *this;
        }

        currency::operator value_type() const
        {
            return value();
        }

        bool currency::operator==(const currency &rhs) const
        {
            return gold_ == rhs.gold_ && silver_ == rhs.silver_;
        }
        bool currency::operator!=(const currency &rhs) const
        {
            return gold_ != rhs.gold_ || silver_ != rhs.silver_;
        }
        bool currency::operator>(const currency &rhs) const
        {
            return gold_ > rhs.gold_ && silver_ > rhs.silver_;
        }
        bool currency::operator<(const currency &rhs) const
        {
            return gold_ < rhs.gold_ && silver_ < rhs.silver_;
        }
        bool currency::operator>=(const currency &rhs) const
        {
            return gold_ >= rhs.gold_ && silver_ >= rhs.silver_;
        }
        bool currency::operator<=(const currency &rhs) const
        {
            return gold_ <= rhs.gold_ && silver_ <= rhs.silver_;
        }

        currency &currency::normalize()
        {
            while (silver_ > 100) {
                gold_++;
                silver_ -= 100;
            }
            return *this;
        }

        currency &currency::add(const currency &value)
        {
            silver_ += value;
            return normalize();
        }

        currency &currency::subtract(const currency &value)
        {
            value_type temp = value;
            while (temp > silver_) {
                gold_--;
                silver_ += 100;
            }
            silver_ -= temp;
            return *this;
        }

        currency &currency::operator++()
        {
            return add(1);
        }

        currency &currency::operator--()
        {
            return subtract(1);
        }

        currency currency::operator++(int i) const
        {
            currency temp(*this);
            return temp.operator++();
        }

        currency currency::operator--(int i) const
        {
            currency temp(*this);
            return temp.operator--();
        }

        bool currency::operator!() const
        {
            return silver_ == 0 && gold_ == 0;
        }

        currency &currency::multiply(const currency &rhs)
        {
            silver_ *= rhs.silver_;
            gold_ *= rhs.gold_;
            return normalize();
        }

        currency currency::operator*(const currency &rhs)
        {
            currency temp(*this);
            return temp.multiply(rhs);
        }

        currency currency::operator+(const currency &rhs)
        {
            currency temp(*this);
            return temp.add(rhs);
        }

        currency currency::operator-(const currency &rhs)
        {
            currency temp(*this);
            return temp.subtract(rhs);
        }
        currency currency::operator/(const currency &rhs)
        {
            currency temp(*this);
            return temp.divide(rhs);
        }

        currency currency::operator%(const currency &rhs)
        {
            currency temp(*this);
            return temp.mod(rhs);
        }

        currency &currency::operator*=(const currency &rhs)
        {
            return multiply(rhs);
        }

        currency &currency::operator+=(const currency &rhs)
        {
            return add(rhs);
        }
        currency &currency::operator-=(const currency &rhs)
        {
            return subtract(rhs);
        }

        currency &currency::operator/=(const currency &rhs)
        {
            return divide(rhs);
        }
        currency &currency::operator%=(const currency &rhs)
        {
            return mod(rhs);
        }

        currency::value_type currency::value() const
        {
            return gold_ * value_type(1000) + silver_;
        }

        currency::value_type currency::copper() const
        {
            return silver_ % 10;
        }
        currency::value_type currency::silver() const
        {
            return silver_;
        }
        void currency::silver(const value_type &value)
        {
            silver_ = value;
            normalize();
        }

        currency::value_type currency::gold() const
        {
            return gold_;
        }
        void currency::gold(const value_type &value)
        {
            gold_ = value;
        }

        currency::value_type currency::platinum() const
        {
            return gold_ / 1000UL;
        }

        string currency::to_string() const
        {
            return format("$.2f") << (gold_ * 100.0) + silver_;
        }

        string currency::to_string(const string &fmt) const
        {
            if (fmt == "P") {
                return format("${0:2f}") << (gold_ / 1000.0);
            } else if (fmt == "G") {
                return format("${0:2f}") << gold_ + (silver_ / 100.0);
            } else if (fmt == "S") {
                return format("${0:2f}") << silver_ / 100.0;
            } else if (fmt == "C") {
                return format("${0:2f}") << (silver_ % 10) / 100.0;
            } else {
                return to_string();
            }
        }

        currency &currency::divide(const currency &rhs)
        {
            gold_ /= rhs.gold_;
            silver_ /= rhs.silver_;

            return normalize();
        }

        currency &currency::mod(const currency &rhs)
        {
            gold_ %= rhs.gold_;
            silver_ %= rhs.silver_;

            return normalize();
        }
    }
}