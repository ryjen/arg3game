#include <bandit/bandit.h>
#include "util.h"
#include <arg3str/util.h>

using namespace bandit;
using namespace arg3::game;


go_bandit([]() {
    describe("string utils", []() {
        it("can get lines", []() {
            string tmp("this\nis a\n\rtest");

            string buf;

            string::const_iterator it = tmp.begin();

            arg3::game::get_line(it, tmp.end(), buf);

            Assert::That(arg3::equals("this", buf), Equals(true));

            arg3::game::get_line(it, tmp.end(), buf);

            Assert::That(arg3::equals("is a", buf), Equals(true));

            arg3::game::get_line(it, tmp.end(), buf);

            Assert::That(arg3::equals("test", buf), Equals(true));
        });
    });

    it("can count lines", []() { Assert::That(arg3::game::count_lines("this\nis a\n\rtest"), Equals(2)); });
});
