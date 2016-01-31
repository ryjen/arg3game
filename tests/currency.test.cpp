#include <bandit/bandit.h>
#include "currency.h"

using namespace bandit;
using namespace arg3::game;

go_bandit([]() {
    describe("currency", []() {


        it("can be constructed", []() {
            currency m;

            Assert::That(m.gold(), Equals(0));
            Assert::That(m.silver(), Equals(0));
        });

        it("can be silver", []() {
            currency m(1213);

            Assert::That(m.silver(), Equals(13));
            Assert::That(m.gold(), Equals(12));

            currency n(9);

            Assert::That(n.silver(), Equals(9));
            Assert::That(n.gold(), Equals(0));
        });

        it("can be gold and silver", []() {
            currency m(123, 45);

            Assert::That(m.silver(), Equals(45));
            Assert::That(m.gold(), Equals(123));

            currency n(150, 150);

            Assert::That(n.silver(), Equals(50));
            Assert::That(n.gold(), Equals(151));
        });

        it("can be assigned", []() {
            currency m(400, 34);

            currency c = m;

            Assert::That(c.gold(), Equals(400));
            Assert::That(c.silver(), Equals(34));
        });
    });
});
