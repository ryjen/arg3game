#include <bandit/bandit.h>
#include "player.h"

using namespace bandit;
using namespace arg3::game;

go_bandit([]() {
    describe("a player", []() {
        it("has a primary column", []() {

            Assert::That(db::reference_id_name<character>(), Equals("character_id"));

        });

        it("can set a name", []() {
            player temp;

            temp.set_name("Bob");

            Assert::That(temp.name(), Equals("Bob"));
        });
    });
});
