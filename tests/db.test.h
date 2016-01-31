#ifndef ARG3_GAME_TEST_DB_H
#define ARG3_GAME_TEST_DB_H

#include "db.h"
#include <unistd.h>

class test_db : public arg3::game::database
{
   public:
    test_db();

    void setup();

    void teardown();
};

extern test_db testdb;

class test_record : public arg3::game::record<test_record>
{
   public:
    constexpr static const char *const TABLE_NAME = "entities";

    test_record();

    void to_storage(arg3::game::storage_builder &obj) const
    {
    }

    void from_storage(const arg3::game::storage &obj)
    {
    }
};

#endif
