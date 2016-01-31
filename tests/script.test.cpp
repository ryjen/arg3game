#include <bandit/bandit.h>
#include "script.h"
#include "npc.h"

using namespace bandit;
using namespace arg3::game;

go_bandit([]() {

    describe("a script", []() {

        it("can return values", []() {

            npc temp;

            temp.set_name("bob");

            script script("return obj:name();");

            script.push("obj", &temp);

            script.execute();

            string val = script.get_string(1);

            Assert::That(val, Equals("bob"));
        });

    });


});
