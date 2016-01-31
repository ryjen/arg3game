#include <bandit/bandit.h>
#include "db.test.h"
#include "stacktrace.h"

using namespace bandit;
using namespace arg3::game;


test_db testdb;

test_db::test_db() : database("game_test")
{
}

void test_db::setup()
{
    open("localhost");
    remove("entities", storage());
    // execute("create table if not exists entities(id integer primary key autoincrement, entity_id varchar(45), sdata varchar(45), idata integer,
    // fdata real)");
    // execute("delete from entities");
    // // reset the primary key auto increment so its always '1'
    // execute("delete from sqlite_sequence where name='entities'");
    // execute("insert into entities(entity_id, sdata, idata, fdata) values('entity123', 'hello, world', 1234, 123.456)");
}

void test_db::teardown()
{
    // close();
    // unlink(connection_string().c_str());
}

test_record::test_record()
{
}

go_bandit([]() {

    describe("a database", []() {
        before_each([]() { testdb.setup(); });

        after_each([]() { testdb.teardown(); });

        // Spec(can_open_database)
        // {
        //     Assert::That(database::instance()->is_open(), Equals(true));
        // }

        it("a record has an id column", []() {
            test_record record;

            Assert::That(record.ref_id_name(), Equals("entity_id"));
        });

        // Spec(primary_key_value)
        // {
        //     vector<string> columns = { "id", "entity_id", "sdata", "idata", "fdata" };

        //     select_query query("entities", &testdb);

        //     arg3::game::id_t value = query.execute_scalar<arg3::game::id_t>();;

        //     Assert::That(value, Equals(1));
        // }
    });
});
