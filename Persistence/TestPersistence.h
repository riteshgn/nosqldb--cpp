#pragma once
///////////////////////////////////////////////////////////////////////
// TestPersistence.h - Implements all test cases for Persistence     //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This file implements the test functors for testing Persistence

* Required Files:
* ---------------
* Persistence.h, Persistence.cpp
* XmlDocument.h, XmlDocument.cpp
* XmlElement.h, XmlElement.cpp
* DbTestHelper.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 08 Feb 2018
* - first release
*/
#ifndef TEST_PERSISTENCE_H
#define TEST_PERSISTENCE_H

#include "Persistence.h"
#include "../DbTestHelper/DbTestHelper.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"

#include <iostream>

namespace NoSqlDbTests {
    /////////////////////////////////////////////////////////////////////
    // test functors
    // - Implements test cases to demonstrate the various requirements 
    //   on Persistence module
    class test8a : public Test::AbstractTest { 
    public:
        test8a(AbstractTest::TestTitle title) : AbstractTest(title) {  }
        virtual bool operator()(); 
    };
    class test8b : public Test::AbstractTest { 
    public:
        test8b(AbstractTest::TestTitle title) : AbstractTest(title) {  }
        virtual bool operator()(); 
    };
    class test11a : public Test::AbstractTest {
    public:
        test11a(AbstractTest::TestTitle title) : AbstractTest(title) {  }
        virtual bool operator()();
    };
    class test11b : public Test::AbstractTest {
    public:
        test11b(AbstractTest::TestTitle title) : AbstractTest(title) {  }
        virtual bool operator()();
    };

    // test functions

    //----< demo exporting to XML requirement #8a >------------------------------------------

    bool test8a::operator()()
    {
        using namespace NoSqlDb;
        using namespace XmlProcessing;

        DbCore<std::string> db = createTitanDb();
        showInitialDbState(db);

        Persistence<std::string> persistence(db, "The Titans");
        persistence.exportDb(db.keys(), "../db_shards/titans.xml");

        std::cout << "\n  A visual examination of the generated file '../db_shards/titans.xml' "
            << "will show that the db state has been persisted.";
        putLine();

        XmlDocument xmlDoc("../db_shards/titans.xml", XmlDocument::file);
        std::cout << "\n" << xmlDoc.toString();
        putLine(2);

        // clean up and return
        DbProvider dbp;
        dbp.db() = db;
        putLine(2);

        setMessage("Persisting to XML file");
        return true;
    }

    //----< demo importing from XML requirement #8b >------------------------------------------

    bool test8b::operator()()
    {
        using namespace NoSqlDb;
        using namespace XmlProcessing;

        DbProvider dbp;
        DbCore<std::string> db = dbp.db();

        showInitialDbState(db);

        XmlDocument xmlDoc("../db_shards/titans-reloaded.xml", XmlDocument::file);
        std::cout << "\n Restoring below data from xml file '../db_shards/titans-reloaded.xml'";
        std::cout << "\n" << xmlDoc.toString();
        putLine(2);

        Persistence<std::string> persistence(db);
        persistence.importDb("../db_shards/titans-reloaded.xml");

        if (!db.contains("poseidon") || !db.contains("leto"))
        {
            setMessage("New elements from xml file are not added");
            return false;
        }

        if (db["leto"].metadata().children().size() != 2)
        {
            setMessage("New elements' children from xml file are not added");
            return false;
        }

        std::cout << "\n  new elements get added " <<
            "after restoring from xml and preserving original values: ";
        showDb(db);
        putLine(2);

        persistence.importDb("../db_shards/titans-reloaded.xml", false);

        if (db["kronos"].metadata().children().size() != 2)
        {
            setMessage("New relationships from xml file are not added");
            return false;
        }

        std::cout << "\n  new relationship gets added to kronos " <<
            "after restoring from xml and choosing to overwrite existing values: ";
        showDb(db);
        putLine(2);

        setMessage("Restoring from XML file");
        return true;
    }

    //----< demo package structure in XML #11 >------------------------------------------

    void _addSet1PackagesToDb(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;
        // DateTime
        DbElementMetadata metadata;
        metadata.name("DateTime");
        metadata.descrip("The DateTime class represents clock time");
        DbElement<std::string> pkgElem;
        pkgElem.metadata(metadata);
        db["DateTime"] = pkgElem;
        // StringUtilities
        metadata.name("StringUtilities");
        metadata.descrip("Small, generally useful, helper classes");
        pkgElem.metadata(metadata);
        db["StringUtilities"] = pkgElem;
        // XmlDocument
        metadata.name("XmlDocument");
        metadata.descrip("A container of XmlElement nodes");
        pkgElem.metadata(metadata);
        db["XmlDocument"] = pkgElem;
        // DbTestHelper
        metadata.name("DbTestHelper");
        metadata.descrip("Helper utilities for testing framework");
        pkgElem.metadata(metadata);
        db["DbTestHelper"] = pkgElem;
        // DbCore
        metadata.name("DbCore");
        metadata.descrip("Implements NoSql database prototype");
        pkgElem.metadata(metadata);
        db["DbCore"] = pkgElem;
    }

    void _addSet2PackagesToDb(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;
        // Query
        DbElementMetadata metadata;
        metadata.name("Query");
        metadata.descrip("Implements the Query module");
        DbElement<std::string> pkgElem;
        pkgElem.metadata(metadata);
        db["Query"] = pkgElem;
        // Persistence
        metadata.name("Persistence");
        metadata.descrip("Implements the persistence layer");
        pkgElem.metadata(metadata);
        db["Persistence"] = pkgElem;
        // DbPayloads
        metadata.name("DbPayloads");
        metadata.descrip("Payload type for Project#2 repository");
        pkgElem.metadata(metadata);
        db["DbPayloads"] = pkgElem;
        // Executive
        metadata.name("Executive");
        metadata.descrip("Provides an executive interface");
        pkgElem.metadata(metadata);
        db["Executive"] = pkgElem;
        // ConsoleColor
        metadata.name("ConsoleColor");
        metadata.descrip("Change console output color");
        pkgElem.metadata(metadata);
        db["ConsoleColor"] = pkgElem;
        // Test
        metadata.name("Test");
        metadata.descrip("Test Executive framework for NoSqlDb");
        pkgElem.metadata(metadata);
        db["Test"] = pkgElem;
    }

    void _createRelationshipsForPkgs(NoSqlDb::DbCore<std::string>& db)
    {
        using namespace NoSqlDb;
        db["DbCore"]
            .addRelationship("DateTime");

        db["Query"]
            .addRelationship("DateTime")
            .addRelationship("DbCore");

        db["Persistence"]
            .addRelationship("DateTime")
            .addRelationship("DateTime")
            .addRelationship("DbCore");

        db["DbTestHelper"]
            .addRelationship("DateTime")
            .addRelationship("DbCore");

        db["Test"]
            .addRelationship("Executive")
            .addRelationship("StringUtilities")
            .addRelationship("DateTime")
            .addRelationship("XmlDocument")
            .addRelationship("DbCore")
            .addRelationship("Query")
            .addRelationship("Persistence")
            .addRelationship("DbPayloads")
            .addRelationship("ConsoleColor");
    }

    bool test11a::operator()()
    {
        using namespace NoSqlDb;

        DbCore<std::string> db;
        _addSet1PackagesToDb(db);
        _addSet2PackagesToDb(db);
        _createRelationshipsForPkgs(db);

        Persistence<std::string> persistence(db, "Project#1 Spring 2018");
        persistence.exportDb(db.keys(), "../db_shards/nosqldb_package_structure.xml");

        std::cout << "\n  project package structure has been saved to file" <<
            "'../db_shards/nosqldb_package_structure.xml'\n";
        putLine();

        setMessage("Generated package structure XML");
        return true;
    }

    bool test11b::operator()()
    {
        using namespace NoSqlDb;

        DbCore<std::string> db;
        Persistence<std::string> persistence(db);

        persistence.importDb("../db_shards/nosqldb_package_structure.xml");

        std::cout << "\n  project package structure has been loaded from file" <<
            "'../db_shards/nosqldb_package_structure.xml'\n";

        showDb(db);
        putLine(2);

        setMessage("Loaded package structure XML");
        return true;
    }
}

#endif // !TEST_PERSISTENCE_H