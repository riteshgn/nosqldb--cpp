#pragma once
///////////////////////////////////////////////////////////////////////
// TestRepoPayload.h - Implements all test cases for RepoPayload     //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This file implements the test functors for testing the RepoPayload

* Required Files:
* ---------------
* RepoPayload.h, RepoPayload.cpp
* DbCore.h, DbCore.cpp
* Query.h, Query.cpp
* Persistence.h, Persistence.cpp
* DateTime.h, DateTime.cpp
* DbTestHelper.h
*
* Maintenance History:
* --------------------
* ver 1.1 : 10 Feb 2018
* - added test case for query by category
* ver 1.0 : 09 Feb 2018
* - first release
*/

#ifndef TEST_REPO_PAYLOAD_H
#define TEST_REPO_PAYLOAD_H

#include "RepoPayload.h"
#include "../DbCore/DbCore.h"
#include "../Query/Query.h"
#include "../Persistence/Persistence.h" 
#include "../DbTestHelper/DbTestHelper.h"

namespace NoSqlDbTests
{
    /////////////////////////////////////////////////////////////////////
    // test9 functor
    // - Implements test case to demonstrate the Repository Payload requirement

    class test9 : public Test::AbstractTest
    {
    public:
        test9(AbstractTest::TestTitle title) : AbstractTest(title) {};
        virtual bool operator()();
    };

    class categoryHeader : public NoSqlDb::IPayloadSearchCriteria<Repository::RepoPayload>
    {
        virtual bool operator()(const Repository::RepoPayload& payload)
        {
            using Category = std::string;
            for (Category category : payload.categories())
            {
                if (category == "Header")
                    return true;
            }
            return false;
        }
    };

    // test functions

    //----< generates data in db for performing the test >---------------------

    void _populateTestData(NoSqlDb::DbCore<Repository::RepoPayload>& db)
    {
        using namespace NoSqlDb;
        using namespace Repository;

        DbElementMetadata metadata;
        metadata.name("DateTime.h");
        metadata.descrip("The DateTime header file");

        RepoPayload payload;
        payload.filePath("/home/user/NoSqlDb/DateTime/");
        payload.categories({ "Header" });

        DbElement<RepoPayload> element;
        element.metadata(metadata);
        element.payLoad(payload);
        db["DateTime.h"] = element;

        metadata.name("DateTime.cpp");
        metadata.descrip("The DateTime application file");

        payload.filePath("/home/user/NoSqlDb/DateTime/");
        payload.categories({ "StaticLibrary" });

        element.metadata(metadata);
        element.payLoad(payload);
        db["DateTime.cpp"] = element;

        metadata.name("DbCore.h");
        metadata.descrip("The DbCore header file");

        payload.filePath("/home/user/NoSqlDb/DbCore/");
        payload.categories({ "Header" });

        element.metadata(metadata);
        element.payLoad(payload);
        db["DbCore.h"] = element;

        metadata.name("DbCore.cpp");
        metadata.descrip("The DbCore application file");

        payload.filePath("/home/user/NoSqlDb/DbCore/");
        payload.categories({ "Application" });

        element.metadata(metadata);
        element.payLoad(payload);
        db["DbCore.cpp"] = element;
    }

    //----< demo custom payload requirement #9 >---------------------
    bool test9::operator()()
    {
        using namespace NoSqlDb;
        using namespace Repository;

        DbCore<RepoPayload> db;
        showInitialDbState(db);

        _populateTestData(db);
        if (db.size() != 4)
        {
            setMessage("Expected db to have 4 elements");
            return false;
        }

        std::cout << "\n  after adding elements with keys: ";
        DbCore<RepoPayload>::Keys keys = db.keys();
        showKeys(db);
        putLine();

        std::cout << "\n  make all header files children of respective cpp files";
        db["DateTime.cpp"].addRelationship("DateTime.h");
        db["DbCore.cpp"]
            .addRelationship("Date.h")
            .addRelationship("DbCore.h");

        putLine();
        std::cout << "\n  showing all the database elements:";
        showDb(db);
        putLine();

        Query<RepoPayload> query;
        categoryHeader categoryHeader;
        DbCore<RepoPayload> result = query.from(db).where.payload.has(categoryHeader).end();

        putLine();
        std::cout << "\n  Demonstrating custom payload query: ";
        std::cout << "\n  code> query.from(db).where.payload.has(categoryHeader).end()\n";
        showDb(result);
        putLine();

        /*Persistence<RepoPayload> persistence(db);
        persistence.exportDb(db.keys(), "../db_shards/test_repopayload.xml");*/

        // clean up and return
        putLine(2);

        setMessage("Adding custom payload to NoSQlDb");
        return true;
    }
}

#endif // !TEST_REPO_PAYLOAD_H
