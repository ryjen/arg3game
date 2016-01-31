#include <bandit/bandit.h>
#include "area.h"
#include "dungeon.h"

using namespace bandit;
using namespace arg3::game;

go_bandit([]() {

    describe("a dungeon", []() {
        it("can generate a map", []() {

            arg3::log::set_min_log_level(arg3::LOG_TRACE);

            dungeon d;

            if (d.generate(80, 25, 100)) {
                cout << d.to_string() << endl;
            }

            auto area = d.to_area("test");
        });
    });

});
