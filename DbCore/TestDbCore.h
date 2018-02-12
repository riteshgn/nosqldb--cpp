#pragma once
///////////////////////////////////////////////////////////////////////
// TestDbCore.h - Implements all test cases for DbCore               //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This file implements the test functors for testing the DbCore

* Required Files:
* ---------------
* DbCore.h, DbCore.cpp
* DbTestHelper.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 09 Feb 2018
* - first release
*/

#ifndef TEST_DBCORE_H
#define TEST_DBCORE_H

#include "DbCore.h"
#include "../DbTestHelper/DbTestHelper.h"

namespace NoSqlDbTests {

    /////////////////////////////////////////////////////////////////////
    // test functors
    // - Implements test cases to demonstrate the various requirements 
    //   on DbCore module

    class test1 : public Test::AbstractTest {
    public:
        test1(AbstractTest::TestTitle title) : AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test2 : public Test::AbstractTest {
    public:
        test2(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test3a : public Test::AbstractTest {
    public:
        test3a(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test3b : public Test::AbstractTest {
    public:
        test3b(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test4a : public Test::AbstractTest {
    public:
        test4a(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test4b : public Test::AbstractTest {
    public:
        test4b(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test5a : public Test::AbstractTest {
    public:
        test5a(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test5b : public Test::AbstractTest {
    public:
        test5b(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test5c : public Test::AbstractTest {
    public:
        test5c(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test5d : public Test::AbstractTest {
    public:
        test5d(Test::AbstractTest::TestTitle title) : Test::AbstractTest(title) {  }
        virtual bool operator()();
    };

    // test functions

    //----< demo requirement #1 >------------------------------------------

    bool test1::operator()()
    {
        std::cout << "\n  " << typeid(std::function<bool()>).name()
            << ", declared in this function, "
            << "\n  is only valid for C++11 and later versions.";
        putLine(2);

        setMessage("Use C++11");
        return true; // would not compile unless C++11
    }

    //----< demo requirement #2 >------------------------------------------

    bool test2::operator()()
    {
        std::cout << "\n  A visual examination of all the submitted code "
            << "will show only\n  use of streams and operators new and delete.";
        putLine(2);

        setMessage("Use streams and new and delete");
        return true;
    }

    //----< demo first part of requirement #3 >----------------------------

    bool test3a::operator()()
    {
        using namespace NoSqlDb;

        std::cout << "\n  Creating a db element with key \"Fawcett\":";

        // create database to hold std::string payload
        DbCore<std::string> db;
        DbProvider dbp;
        dbp.db() = db;

        // create some demo elements and insert into db
        DbElementMetadata demoElemMeta;
        demoElemMeta.name("Jim");
        demoElemMeta.descrip("Instructor for CSE687");
        demoElemMeta.dateTime(DateTime().now());
        DbElement<std::string> demoElem;
        demoElem.metadata(demoElemMeta);
        demoElem.payLoad("The good news is ...");

        if (demoElem.metadata().name() != "Jim")
        {
            setMessage("Name was not set");
            return false;
        }    
        if (demoElem.metadata().descrip() != "Instructor for CSE687")
        {
            setMessage("Description was not set");
            return false;
        }
        if (demoElem.metadata().dateTime().now() != DateTime().now())
        {
            setMessage("DateTime was not set");
            return false;
        }
        if (demoElem.payLoad() != "The good news is ...")
        {
            setMessage("Payload was not set");
            return false;
        }

        showHeader();
        showElem(demoElem);

        db["Fawcett"] = demoElem;
        dbp.db() = db;
        putLine(2);

        setMessage("Create DbElement<std::string>");
        return true;
    }
    //----< demo second part of requirement #3 >---------------------------

    void _addEntriesToDb(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;

        DbElementMetadata demoElemMeta;
        demoElemMeta.name("Ammar");
        demoElemMeta.descrip("TA for CSE687");

        DbElement<std::string> demoElem = db["Fawcett"];
        demoElem.metadata(demoElemMeta);
        demoElem.payLoad("You should try ...");
        db["Salman"] = demoElem;

        demoElemMeta.name("Jianan");

        demoElem.metadata(demoElemMeta);
        demoElem.payLoad("Dr. Fawcett said ...");
        db["Sun"] = demoElem;

        demoElem.payLoad("You didn't demonstrate Requirement #4");
        demoElemMeta.name("Nikhil");
        demoElem.metadata(demoElemMeta);
        db["Prashar"] = demoElem;

        demoElem.payLoad("You didn't demonstrate Requirement #5");
        demoElemMeta.name("Pranjul");
        demoElem.metadata(demoElemMeta);
        db["Arora"] = demoElem;

        demoElem.payLoad("You didn't demonstrate Requirement #6");
        demoElemMeta.name("Akash");
        demoElem.metadata(demoElemMeta);
        db["Anjanappa"] = demoElem;
    }

    void _addChildren(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;

        std::cout << "\n  make all the new elements children of element with key \"Fawcett\"";
        db["Fawcett"].metadata().children().push_back("Salman");
        db["Fawcett"].metadata().children().push_back("Sun");
        db["Fawcett"].metadata().children().push_back("Prashar");
        db["Fawcett"].metadata().children().push_back("Arora");
        db["Fawcett"].metadata().children().push_back("Anjanappa");

        showHeader();
        showElem(db["Fawcett"]);

        db["Salman"].metadata().children().push_back("Sun");
        db["Salman"].metadata().children().push_back("Prashar");
        db["Salman"].metadata().children().push_back("Arora");
        db["Salman"].metadata().children().push_back("Anjanappa");
    }

    bool test3b::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        _addEntriesToDb(db);

        if (!db.contains("Salman"))
        {
            setMessage("Element not found");
            return false;
        }

        if (db.size() != 6)
        {
            setMessage("Not all elements were added");
            return false;
        }

        std::cout << "\n  after adding elements with keys: ";
        DbCore<std::string>::Keys keys = db.keys();
        showKeys(db);
        putLine();

        _addChildren(db);

        // display the results

        putLine();
        std::cout << "\n  showing all the database elements:";
        showDb(db);
        putLine();

        std::cout << "\n  database keys are: ";
        showKeys(db);

        // clean up and return
        db.truncate();
        dbp.db() = db;
        putLine(2);

        setMessage("Create DbCore<std::string>");
        return true;
    }

    //----< demo add element requirement #4a >-----------------------

    bool test4a::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        showInitialDbState(db);

        std::unordered_map<std::string, DbElement<std::string>> records;

        DbElementMetadata metadata;
        metadata.name("Kronos");
        metadata.descrip("The youngest Titan");
        metadata.dateTime(DateTime().now());

        DbElement<std::string> element1;
        element1.metadata(metadata);
        element1.payLoad("The leader");
        records["kronos"] = element1;

        metadata.name("Zeus");
        metadata.descrip("The King of Gods");
        metadata.dateTime(DateTime().now());

        DbElement<std::string> element2;
        element2.metadata(metadata);
        element2.payLoad("God of Thunder");
        records["zeus"] = element2;

        db.add(records);

        if (db.size() != 2)
        {
            setMessage("Addition of key value pairs did not work as expected");
            return false;
        }

        std::cout << "\n  showing all the database elements after adding Zeus";
        showDb(db);
        putLine();

        std::cout << "\n  database keys are: ";
        showKeys(db);

        dbp.db() = db;
        putLine(2);
        setMessage("Adding key/value pairs to DB");
        return true;
    }

    //----< demo add element requirement #4b >-----------------------

    bool test4b::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        showInitialDbState(db);

        // expect test data set from #4a to be available
        if (db.size() != 2)
            return false;

        db.remove("kronos");

        if (db.size() != 1)
            return false;

        std::cout << "\n  showing all the database elements after removing Kronos: ";
        showDb(db);
        putLine();

        db.remove("kronos");
        std::cout << "\n  trying to remove Kronos again does not cause the DB to crash ";
        putLine();

        db.remove("zeus");

        if (db.size() != 0)
            return false;

        std::cout << "\n  showing all the database elements after removing Zeus: ";
        showDb(db);
        putLine();

        // clean up and return
        dbp.db() = db;
        putLine(2);

        setMessage("Removing elements from DB");
        return true;
    }

    //----< demo add relationship requirement #5a >-----------------------

    bool test5a::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = createTitanDb(false);

        if (db.size() != 4)
        {
            setMessage("Expected 4 elements in DB");
            return false;
        }
        showInitialDbState(db);

        // demo add relationship using db element
        db["zeus"]
            .addRelationship("apollo")
            .addRelationship("artemis");

        DbElement<std::string> actualElem = db["zeus"];
        if (actualElem.metadata().children().size() != 2)
        {
            setMessage("Expected two children");
            return false;
        }

        std::cout << "\n  showing all the database elements after adding Apollo & Artemis as children of Zeus: ";
        showDb(db);
        putLine();

        // demo add relationship using db core
        db.addRelationship("kronos", "zeus");
        db.addRelationship("kronos", "zeus");

        actualElem = db["kronos"];
        if (actualElem.metadata().children().size() != 1)
        {
            setMessage("Expected only one child");
            return false;
        }

        std::cout << "\n  showing all the database elements after adding Zeus as a child of Kronos twice: ";
        showDb(db);
        putLine();

        // clean up and return
        dbp.db() = db;
        putLine(2);
        setMessage("Adding relationships");
        return true;
    }

    //----< demo remove relationship requirement #5b >-----------------------

    bool test5b::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        if (db.size() != 4)
        {
            setMessage("Expected only 4 elements in DB");
            return false;
        }

        showInitialDbState(db);

        db["kronos"].removeRelationship("apollo");
        std::cout << "\n  trying to remove a non-existent relationship (kronos -> apollo) does not cause the DB to crash ";
        putLine();

        // demo remove relationship using db core
        db.removeRelationship("zeus", "apollo");
        // demove remove relationship using db element
        db["kronos"].removeRelationship("zeus");

        DbElement<std::string> actualElem = db["zeus"];
        if (actualElem.metadata().children().size() != 1)
        {
            setMessage("Expected only one child");
            return false;
        }

        std::cout << "\n  showing all the database elements after removing Apollo's " <<
            "relationship with Zeus and Zeus's relationship with Kronos: ";
        showDb(db);
        putLine(2);

        setMessage("Removing relationships");
        return true;
    }

    //----< demo editing metadata requirement #5c >-----------------------

    bool test5c::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        if (db.size() != 4)
            return false;

        showInitialDbState(db);

        db["zeus"].metadata().name("God of Thunder");
        db["kronos"].metadata().descrip("The leader of Titans");

        if (db["zeus"].metadata().name() != "God of Thunder")
        {
            setMessage("Name not edited");
            return false;
        }

        if (db["kronos"].metadata().descrip() != "The leader of Titans")
        {
            setMessage("Description not edited");
            return false;
        }

        std::cout << "\n  showing all the database elements after updating Zeus's name and Kronos' description : ";
        showDb(db);
        putLine(2);

        setMessage("Editing metadata");
        return true;
    }

    //----< demo replacing payload #5d >-----------------------

    bool test5d::operator()()
    {
        using namespace NoSqlDb;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        if (db.size() != 4)
        {
            setMessage("Expected 4 items in DB");
            return false;
        }

        showInitialDbState(db);

        // demo of replacing payload using db core
        db.replacePayLoad("apollo", "Now lives in the Vatican Museum");
        // demo of replacing payload using db element
        db["artemis"].payLoad("Now lives in The Louvre");

        if (db["apollo"].payLoad() != "Now lives in the Vatican Museum")
        {
            setMessage("payload for apollo not changed");
            return false;
        }

        if (db["artemis"].payLoad() != "Now lives in The Louvre")
        {
            setMessage("payload for artemis not changed");
            return false;
        }

        std::cout << "\n  showing all the database elements after updating Apollo's and Artemis' payload : ";
        showDb(db);
        putLine(2);

        setMessage("Replacing payload");
        return true;
    }

}

#endif // !TEST_DBCORE_H
