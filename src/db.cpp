#include "db.h"

namespace arg3
{
    namespace game
    {
        database db_instance("arg3game");

        database::database(const string &name) : dbName_(name)
        {
        }

        bool database::open(const string &host)
        {
            string err;
            conn_.connect(host, err);
            return err.size() == 0;
        }

        bool database::save(const string &collection, const mongo::BSONObj &obj)
        {
            conn_.insert(dbName_ + "." + collection, obj);
            return true;
        }

        shared_ptr<mongo::DBClientCursor> database::query(const string &collection, const mongo::BSONObj &obj)
        {
            return conn_.query(dbName_ + "." + collection, obj);
        }

        bool database::remove(const string &collection, const storage &obj)
        {
            conn_.remove(dbName_ + "." + collection, obj);
            return true;
        }

        string database::name() const
        {
            return dbName_;
        }
    }
}