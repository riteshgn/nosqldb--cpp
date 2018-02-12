#pragma once
///////////////////////////////////////////////////////////////////////
// DbTestHelper.h - Implements helper utilities which are used by    //
//                  the testing framework                            //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package implements the test utilities

* Required Files:
* ---------------
* DateTime.h, DateTime.cpp
* DbCore.h, DbCore.cpp
*
* Maintenance History:
* --------------------
* ver 1.0 : 08 Feb 2018
* - first release
*/

#ifndef DBTEST_HELPER_H
#define DBTEST_HELPER_H

#include "../DateTime/DateTime.h"

namespace NoSqlDbTests {

    ///////////////////////////////////////////////////////////////////////
    // test helper functions

    // Helpers for time manipulation which will be used in testing queries
    using Duration = std::chrono::system_clock::duration;
    Duration tenMins = DateTime::makeDuration(0, 10, 0, 0);
    Duration oneDay = DateTime::makeDuration(24, 0, 0, 0);
    Duration oneAndHalfDays = DateTime::makeDuration(36, 0, 0, 0);
    Duration twoDays = DateTime::makeDuration(48, 0, 0, 0);
    Duration threeDays = DateTime::makeDuration(72, 0, 0, 0);

    DateTime dt = DateTime();
    DateTime now = dt.now();
    DateTime tenMinsAgo = now - tenMins;
    DateTime oneDayAgo = now - oneDay;
    DateTime oneAndHalfDaysAgo = now - oneAndHalfDays;
    DateTime twoDaysAgo = now - twoDays;
    DateTime threeDaysAgo = now - threeDays;

    //----< reduce the number of characters to type >----------------------

    auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
    {
        Utilities::putline(n, out);
    };

    ///////////////////////////////////////////////////////////////////////
    // DbProvider class
    // - provides mechanism to share a test database between test functions
    //   without explicitly passing as a function argument.

    class DbProvider
    {
    public:
        NoSqlDb::DbCore<std::string>& db() { return db_; }
    private:
        static NoSqlDb::DbCore<std::string> db_;
    };

    NoSqlDb::DbCore<std::string> DbProvider::db_;

    //----< prints the db state during initialization of a test >----------------------

    template<typename T>
    void showInitialDbState(NoSqlDb::DbCore<T>& db)
    {
        std::cout << "\n  showing all the database elements before beginning test: ";

        if (db.size() == 0)
        {
            std::cout << "\n    - DATABASE IS EMPTY -\n\n";
        }
        else 
        {
            showDb(db);
            putLine();

            std::cout << "\n  database keys are: ";
            showKeys(db);
            putLine();
        }
    }

    //----< adds child relationships to the provided Titan DB instance >----------------------

    void _addChildrenInTitanDb(NoSqlDb::DbCore<std::string>& db)
    {
        db["kronos"].addRelationship("zeus");
        db["zeus"]
            .addRelationship("artemis")
            .addRelationship("apollo");
    }

    //----< adds two characters to the provided Titan DB instance >----------------------

    void _addPosiedonAndLeto(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;

        DbElementMetadata metadata;
        metadata.name("Leto");
        metadata.descrip("Goddess of Motherhood");
        metadata.dateTime(oneAndHalfDaysAgo);

        DbElement<std::string> demoElement;
        demoElement.metadata(metadata);
        demoElement.payLoad("Lives at Delos");
        db.add("leto", demoElement);

        metadata.name("Poseidon");
        metadata.descrip("God of the Sea");
        metadata.dateTime(tenMinsAgo);

        demoElement.metadata(metadata);
        demoElement.payLoad("Lives in the Sea");
        db.add("poseidon", demoElement);

        db["leto"]
            .addRelationship("artemis")
            .addRelationship("apollo");
    }

    //----< creates a test DB instance >----------------------

    NoSqlDb::DbCore<std::string> createTitanDb(
        bool includeRelationships = true, bool includePosiedonAndLeto = false)
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();
        db.truncate();

        DbElementMetadata metadata;
        metadata.name("Kronos");
        metadata.descrip("Youngest Titan");
        metadata.dateTime(twoDaysAgo);

        DbElement<std::string> demoElement;
        demoElement.metadata(metadata);
        demoElement.payLoad("Lives at Mount Othrys");
        db.add("kronos", demoElement);

        metadata.name("Zeus");
        metadata.descrip("King of Gods");
        metadata.dateTime(oneAndHalfDaysAgo);

        demoElement.metadata(metadata);
        demoElement.payLoad("Lives at Mount Olympus");
        db.add("zeus", demoElement);

        metadata.name("Apollo");
        metadata.descrip("God of Sun");
        metadata.dateTime(tenMinsAgo);

        demoElement.metadata(metadata);
        demoElement.payLoad("Also lives at Mount Olympus");
        db.add("apollo", demoElement);

        metadata.name("Artemis");
        metadata.descrip("Goddess of the Hunt");
        metadata.dateTime(tenMinsAgo);

        demoElement.metadata(metadata);
        demoElement.payLoad("Also lives at Mount Olympus");
        db.add("artemis", demoElement);

        if (includeRelationships)
            _addChildrenInTitanDb(db);

        if (includePosiedonAndLeto)
            _addPosiedonAndLeto(db);

        dbp.db() = db;
        return db;
    }

}

#endif // !DBTEST_HELPER_H