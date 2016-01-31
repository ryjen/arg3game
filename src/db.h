#ifndef ARG3_GAME_DB_H
#define ARG3_GAME_DB_H

#ifndef SWIG
#include <mongo/client/dbclient.h>
#include "entity.h"
#include "util.h"
#include "exception.h"
#include <boost/any.hpp>
#include <arg3log/log.h>
#endif

namespace arg3
{
    namespace game
    {
        typedef mongo::BSONObj storage;

        typedef mongo::BSONObjBuilder storage_builder;

        typedef mongo::OID storage_id;

        class database
        {
           public:
            database(const string &name);
            bool open(const string &host);
            bool save(const string &collection, const storage &obj);
            shared_ptr<mongo::DBClientCursor> query(const string &collection, const storage &obj);
            bool remove(const string &collection, const storage &obj);
            string name() const;

           private:
            std::string dbName_;
            mongo::DBClientConnection conn_;
        };

        extern database db_instance;

        template <typename T>
        class record;


        namespace db
        {
#ifndef SWIG
            constexpr static const char *const COLUMN_ID = "_id";
#endif
            template <typename T>
            inline vector<shared_ptr<T>> find(const storage &obj, database *db = &db_instance)
            {
                auto cursor = db->query(T::TABLE_NAME, obj);

                vector<shared_ptr<T>> items;
                while (cursor->more()) {
                    auto bson = cursor->next();
                    auto item = make_shared<T>();
                    mongo::BSONElement e;
                    if (bson.getObjectID(e)) {
                        item->set(COLUMN_ID, e.OID());
                    }
                    item->from_storage(bson);
                    items.push_back(item);
                }
                return items;
            }

            template <typename T>
            inline string reference_id_name()
            {
                string value = T::TABLE_NAME;

                if (value.length() == 0) {
                    throw game_exception("unset table name for reference id");
                }

                size_t endPos = value.length() - 1;

                if (tolower(value[endPos]) == 's') {
                    value = value.substr(0, endPos);

                    endPos--;
                }

                if (endPos > 1 && tolower(value[endPos]) == 'e' && tolower(value[endPos - 1]) == 'i') {
                    value = value.substr(0, endPos - 1);
                    value = value.append("y");
                }

                return value.append("_id");
            }

            template <typename T>
            inline storage reference(const storage_id &id, database *db = &db_instance)
            {
                if (!id.isSet()) {
                    log::warn("storing reference to unset id in %s", T::TABLE_NAME);
                }

                storage_builder ref;
                ref << "$ref" << T::TABLE_NAME;
                ref << "$id" << id;
                ref << "$db" << db->name();

                return ref.obj();
            }

            template <typename T, typename R>
            inline vector<shared_ptr<T>> find_all_by_reference(const storage_id &id, database *db = &db_instance)
            {
                return find<T>(BSON(reference_id_name<R>() << reference<R>(id, db)), db);
            }

            template <typename T>
            inline shared_ptr<T> from_reference(const storage &obj, database *db = &db_instance)
            {
                auto cursor = db->query(T::TABLE_NAME, BSON(COLUMN_ID << obj[reference_id_name<T>()]["$id"]));

                shared_ptr<T> item = nullptr;

                if (cursor->more()) {
                    auto bson = cursor->next();
                    item = make_shared<T>();
                    mongo::BSONElement e;
                    if (bson.getObjectID(e)) {
                        item->set(COLUMN_ID, e.OID());
                    }
                    item->from_storage(bson);
                }

                return item;
            }

            template <typename T>
            inline vector<shared_ptr<T>> find_all(database *db = &db_instance)
            {
                return find<T>(storage(), db);
            }

            template <typename T, typename R>
            inline vector<shared_ptr<T>> find_all_by_reference(const string &ref_id_name, const storage_id &id, database *db = &db_instance)
            {
                return find<T>(BSON(ref_id_name << reference<R>(id, db)), db);
            }

            template <typename T>
            inline bool save_record(record<T> &rec, database *db = &db_instance)
            {
                storage_builder bson;
                if (rec.has(COLUMN_ID)) {
                    bson << COLUMN_ID << rec.obj_id();
                } else {
                    bson << mongo::GENOID;
                }
                rec.to_storage(bson);
                auto obj = bson.obj();
                db->save(T::TABLE_NAME, obj);
                mongo::BSONElement e;
                if (obj.getObjectID(e)) {
                    rec.set(COLUMN_ID, e.OID());
                    return true;
                } else {
                    log::warn("No object id after saving %s", T::TABLE_NAME);
                    return false;
                }
            }

            template <typename T>
            inline bool delete_record(const storage_id &id, database *db = &db_instance)
            {
                db->remove(T::TABLE_NAME, BSON(COLUMN_ID << id));
                return true;
            }

            template <typename T>
            inline void store_reference(const storage_id &id, storage_builder &obj, database *db = &db_instance)
            {
                obj << reference_id_name<T>() << reference<T>(id, db);
            }
            template <typename T>
            inline void store_reference(const string &column, const storage_id &id, storage_builder &obj, database *db = &db_instance)
            {
                obj << column << reference<T>(id, db);
            }
        }

        template <typename T>
        class record : public entity
        {
            friend class database;

           public:
            record(database *db = &db_instance) : db_(db)
            {
            }
            record(const record &other) : db_(other.db_), values_(other.values_)
            {
            }
#ifndef SWIG
            record(record &&other) : db_(other.db_), values_(std::move(other.values_))
            {
            }

            record &operator=(record &&other)
            {
                db_ = other.db_;
                values_ = std::move(other.values_);
                return *this;
            }

#endif

            record &operator=(const record &other)
            {
                db_ = other.db_;
                values_ = other.values_;
                return *this;
            }

            virtual ~record()
            {
            }

            virtual bool save()
            {
                return db::save_record(*this, db_);
            }

            bool de1ete() const
            {
                return db::delete_record<T>(obj_id(), db_);
            }

            vector<shared_ptr<T>> find(const storage &obj) const
            {
                return db::find<T>(obj, db_);
            }

            vector<shared_ptr<T>> find_all() const
            {
                return db::find_all<T>(db_);
            }

            template <typename R>
            vector<shared_ptr<R>> find_all_by_ref()
            {
                return db::find_all_by_reference<R, T>(obj_id(), db_);
            }

            template <typename R>
            vector<shared_ptr<R>> find_all_by_ref(const string &column)
            {
                return db::find_all_by_reference<R, T>(column, obj_id(), db_);
            }

            virtual void to_storage(storage_builder &obj) const = 0;
            virtual void from_storage(const storage &obj) = 0;

            boost::any get(const string &name) const
            {
                auto it = values_.find(name);

                if (it != values_.end() && !it->second.empty()) {
                    return it->second;
                }

                return boost::any();
            }

            template <typename V>
            V get(const string &name) const
            {
                auto it = values_.find(name);

                if (it != values_.end()) {
                    return boost::any_cast<V>(it->second);
                }

                return V();
            }

            void set(const string &name, const boost::any &value)
            {
                values_[name] = value;
            }

            bool has(const string &name) const
            {
                return values_.find(name) != values_.end();
            }

            string id() const
            {
                if (!has(db::COLUMN_ID)) {
                    throw game_exception("record has no id set");
                }

                return get<storage_id>(db::COLUMN_ID).str();
            }

            bool is_saved() const
            {
                return has(db::COLUMN_ID) && obj_id().isSet();
            }

            storage_id obj_id() const
            {
                return get<storage_id>(db::COLUMN_ID);
            }

            storage reference() const
            {
                return db::reference(*this, db_);
            }

            void store_reference(storage_builder &obj) const
            {
                db::store_reference<T>(obj_id(), obj, db_);
            }

            void store_reference(const string &column, storage_builder &obj) const
            {
                db::store_reference<T>(column, obj_id(), obj, db_);
            }

            shared_ptr<T> from_reference(const storage &obj) const
            {
                return db::from_reference<T>(obj, db_);
            }

            string ref_id_name() const
            {
                return db::reference_id_name<T>();
            }

            database *db() const
            {
                return db_;
            }

           private:
            database *db_;
            std::unordered_map<std::string, boost::any> values_;
        };
    }
}

#endif
