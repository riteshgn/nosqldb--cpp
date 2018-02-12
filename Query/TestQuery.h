#pragma once
///////////////////////////////////////////////////////////////////////
// TestQuery.h - Implements all test cases for Query                 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This file implements the test functors for testing Query

* Required Files:
* ---------------
* Query.h, Query.cpp
* NoSqlDbTests.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 08 Feb 2018
* - first release
*/

#ifndef TEST_QUERY_H
#define TEST_QUERY_H

#include "Query.h"
#include "../DbTestHelper/DbTestHelper.h"

namespace NoSqlDbTests {
    
    /////////////////////////////////////////////////////////////////////
    // test functors
    // - Implements test cases to demonstrate the various requirements 
    //   on Persistence module

    class test6 : public Test::AbstractTest { 
    public:
        test6(Test::AbstractTest::TestTitle title): Test::AbstractTest(title) {  }
        virtual bool operator()(); 
    private:
        bool _executePart1(NoSqlDb::DbCore<std::string>& db);
        bool _executePart2(NoSqlDb::DbCore<std::string>& db);
    };
    class test7 : public Test::AbstractTest { 
    public:
        test7(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()(); 
    private:
        bool _executePart1(NoSqlDb::DbCore<std::string>& db);
        bool _executePart2(NoSqlDb::DbCore<std::string>& db);
    };

    // test functions

    //----< demo simple querying requirement #6 >------------------------------------------

    bool test6::_executePart1(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;

        Query<std::string> query;
        DbCore<std::string> resultSet = query.from(db).where.key.eq("kronos").end();

        if (resultSet.size() != 1)
        {
            setMessage("Searching results by key");
            return false;
        }

        std::cout << "\n  code>  query.from(db).where.key.eq(\"kronos\").end()\n ";
        showDb(resultSet);
        putLine(2);

        resultSet = query.from(db).where.key.eqRegex("^[aA]{1}(.*)$").end();

        if (resultSet.size() != 2)
        {
            setMessage("Searching results by key with regex");
            return false;
        }

        std::cout << "\n  code>  query.from(db).where.key.eqRegex(\"^[aA]{1}(.*)$\").end()\n ";
        showDb(resultSet);
        putLine(2);

        resultSet = query.from(db).where.child.eq("artemis").end();

        if (resultSet.size() != 2)
        {
            setMessage("Searching results by child key");
            return false;
        }

        std::cout << "\n  code>  query.from(db).where.child.eq(\"artemis\").end()\n ";
        showDb(resultSet);
        putLine(2);

        return true;
    }

    bool test6::_executePart2(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;

        Query<std::string> query;
        DbCore<std::string> resultSet = query.from(db).where.metadata.eqRegex("^(.*)(Goddess)(.*)$").end();

        if (resultSet.size() != 2)
        {
            setMessage("Searching results by metadata regex");
            return false;
        }

        std::cout << "\n  code>  query.from(db).where.metadata.eqRegex(\"^(.*)(Goddess)(.*)$\").end()\n ";
        showDb(resultSet);
        putLine(2);

        resultSet = query.from(db).where.dateTime.between(threeDaysAgo, oneDayAgo).end();

        if (resultSet.size() != 3)
        {
            setMessage("Searching results by datetime between a range");
            return false;
        }

        std::cout << "\n  code>  query.from(db).where.dateTime.between(threeDaysAgo, oneDayAgo).end()\n ";
        showDb(resultSet);
        putLine(2);

        resultSet = query.from(db).where.dateTime.gt(oneDayAgo).end();

        if (resultSet.size() != 3)
        {
            setMessage("Searching results by datetime greater than some value");
            return false;
        }

        std::cout << "\n  code>  query.from(db).where.dateTime.gt(oneDayAgo).end()\n " << oneDayAgo.time();
        showDb(resultSet);
        putLine(2);

        return true;
    }

    bool test6::operator()()
    {
        using namespace NoSqlDb;

        DbCore<std::string> db = createTitanDb(true, true);
        showInitialDbState(db);

        if (_executePart1(db) && _executePart2(db))
        {
            setMessage("Simple querying on the database");
            return true;
        }

        return false;
    }

    //----< demo advanced querying requirement #7 >------------------------------------------

    bool test7::_executePart1(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;

        Query<std::string> query;

        DbCore<std::string> resultSet =
            query.from(db)
            .where.metadata.eqRegex("^(.*)(Goddess)(.*)$")
            .andWhere.dateTime.between(threeDaysAgo, oneDayAgo)
            .end();

        if (resultSet.size() != 1)
        {
            setMessage("Searching results by 'AND'ing ex#1 failed");
            return false;
        }

        std::cout << "\n  code>  query.from(db).where.metadata.eqRegex(goddessRegex)" <<
            ".andWhere.dateTime.between(threeDaysAgo, oneDayAgo).end()\n";
        showDb(resultSet);
        putLine(2);

        resultSet =
            query.from(db)
            .where.dateTime.gt(oneDayAgo)
            .andWhere.metadata.eqRegex("^(.*)(Sea)(.*)$")
            .end();

        if (resultSet.size() != 1)
        {
            setMessage("Searching results by 'AND'ing ex#2 failed");
            return false;
        };

        std::cout << "\n  code>  query.from(db).where.dateTime.gt(oneDayAgo)" <<
            ".andWhere.metadata.eqRegex(seaRegex).end()\n";
        showDb(resultSet);
        putLine();

        return true;
    }

    bool test7::_executePart2(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;

        Query<std::string> query;

        DbCore<std::string> resultSet = query.from(db).where.key.eq("kronos").end();

        std::cout << "\n  code>  query.from(db).where.key.eq(\"kronos\").end() [query#1]\n ";
        showDb(resultSet);
        putLine();

        resultSet = query.from(db).where.child.eq("artemis").end();

        std::cout << "\n  code>  query.from(db).where.child.eq(\"artemis\").end() [query#2]\n ";
        showDb(resultSet);
        putLine(2);

        resultSet =
            query.orThese({
            query.from(db).where.key.eq("kronos").end(),
            query.from(db).where.child.eq("artemis").end()
                }).end();

        if (resultSet.size() != 3)
        {
            setMessage("Searching results by 'OR'ing ex#1 failed");
            return false;
        }

        std::cout << "\n  code> query.orThese({(query#1, query#2)})\n ";
        showDb(resultSet);
        putLine(2);

        return true;
    }

    bool test7::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        showInitialDbState(db);

        if (_executePart1(db) && _executePart2(db))
        {
            setMessage("Advanced querying on the database");
            return true;
        }

        return false;
    }

}

#endif // !TEST_QUERY_H