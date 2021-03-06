///////////////////////////////////////////////////////////////////////
// Persistence.cpp - Implements the persistence APIs                 //
// ver 1.4                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////

/*
* Maintenance History:
* --------------------
* ver 1.4 : 16 Apr 2018
* - switched from std::string as payload to the IPayload implementation - StringPayload
* ver 1.3 : 15 Apr 2018
* - Added tests
* ver 1.2 : 08 Feb 2018
* - pulled tests into the TestPersistence.h file
* ver 1.1 : 06 Feb 2018
* - added modifications required for interface change
* - added more checks in tests
* ver 1.0 : 05 Feb 2018
* - first release
*/

#include "TestPersistence.h"
#include "../DbCore/DbCoreTestHelper.h"
#include "Persistence.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../Payloads/RepoPayload.h"

using namespace NoSqlDbTests;
using namespace NoSqlDb;
using namespace Repository;

// test functions

static DbCore<StringPayload> testDb;

//----< demo exporting to XML requirement #8a >------------------------------------------

bool test8a::operator()()
{
    using namespace NoSqlDb;
    using namespace XmlProcessing;

    DbCore<StringPayload>& db = testDb;
    DbTestHelper::createTitanDb(db);
    DbTestHelper::showInitialDbState(db);

    Persistence<StringPayload> persistence(db, "The Titans");
    persistence.exportDb(db.keys(), "../db_shards/titans.xml");

    std::cout << "\n  A visual examination of the generated file '../db_shards/titans.xml' "
        << "will show that the db state has been persisted.";
    std::cout << "\n";

    XmlDocument xmlDoc("../db_shards/titans.xml", XmlDocument::file);
    std::cout << "\n" << xmlDoc.toString();
    std::cout << "\n\n";

    // clean up and return
    std::cout << "\n\n";

    setMessage("Persisting to XML file");
    return true;
}

//----< demo importing from XML requirement #8b >------------------------------------------

bool test8b::operator()()
{
    using namespace NoSqlDb;
    using namespace XmlProcessing;

    DbCore<StringPayload>& db = testDb;
    DbTestHelper::showInitialDbState(db);

    XmlDocument xmlDoc("../db_shards/titans-reloaded.xml", XmlDocument::file);
    std::cout << "\n Restoring below data from xml file '../db_shards/titans-reloaded.xml'";
    std::cout << "\n" << xmlDoc.toString();
    std::cout << "\n\n";

    Persistence<StringPayload> persistence(db);
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
    std::cout << "\n\n";

    persistence.importDb("../db_shards/titans-reloaded.xml", false);

    if (db["kronos"].metadata().children().size() != 2)
    {
        setMessage("New relationships from xml file are not added");
        return false;
    }

    std::cout << "\n  new relationship gets added to kronos " <<
        "after restoring from xml and choosing to overwrite existing values: ";
    showDb(db);
    std::cout << "\n\n";

    setMessage("Restoring from XML file");
    return true;
}

//----< demo package structure in XML #11 >------------------------------------------

void _addSet1PackagesToDb(NoSqlDb::DbCore<RepoPayload>& db)
{
    // DateTime
    DbElementMetadata metadata;
    metadata.name("DateTime");
    metadata.descrip("The DateTime class represents clock time");
    DbElement<RepoPayload> pkgElem;
    pkgElem.metadata(metadata); 
    pkgElem.payLoad().filePath("Storage/DateTime.h");
    pkgElem.payLoad().categories({ "utility" });
    db["DateTime"] = pkgElem;
    // StringUtilities
    metadata.name("StringUtilities");
    metadata.descrip("Small, generally useful, helper classes");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/StringUtilities.h");
    pkgElem.payLoad().categories({ "utility" });
    db["StringUtilities"] = pkgElem;
    // XmlDocument
    metadata.name("XmlDocument");
    metadata.descrip("A container of XmlElement nodes");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/XmlDocument.h");
    pkgElem.payLoad().categories({ "utility" });
    db["XmlDocument"] = pkgElem;
    // DbTestHelper
    metadata.name("DbTestHelper");
    metadata.descrip("Helper utilities for testing framework");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/DbTestHelper.h");
    pkgElem.payLoad().categories({ "helper" });
    db["DbTestHelper"] = pkgElem;
    // DbCore
    metadata.name("DbCore");
    metadata.descrip("Implements NoSql database prototype");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/DbCore.h");
    db["DbCore"] = pkgElem;
}

void _addSet2PackagesToDb(NoSqlDb::DbCore<RepoPayload>& db)
{
    // Query
    DbElementMetadata metadata;
    metadata.name("Query");
    metadata.descrip("Implements the Query module");
    DbElement<RepoPayload> pkgElem;
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/Query.h");
    db["Query"] = pkgElem;
    // Persistence
    metadata.name("Persistence");
    metadata.descrip("Implements the persistence layer");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/Persistence.h");
    db["Persistence"] = pkgElem;
    // DbPayloads
    metadata.name("DbPayloads");
    metadata.descrip("Payload type for Project#2 repository");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/DbPayloads.h");
    db["DbPayloads"] = pkgElem;
    // Executive
    metadata.name("Executive");
    metadata.descrip("Provides an executive interface");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/Executive.h");
    db["Executive"] = pkgElem;
    // ConsoleColor
    metadata.name("ConsoleColor");
    metadata.descrip("Change console output color");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().filePath("Storage/ConsoleColor.h");
    pkgElem.payLoad().categories({ "utility", "console" });
    db["ConsoleColor"] = pkgElem;
    // Test
    metadata.name("Test");
    metadata.descrip("Test Executive framework for NoSqlDb");
    pkgElem.metadata(metadata);
    pkgElem.payLoad().categories({});
    pkgElem.payLoad().filePath("Storage/Test.h");
    db["Test"] = pkgElem;
}

void _createRelationshipsForPkgs(DbCore<RepoPayload>& db)
{
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

    DbCore<RepoPayload> db;
    _addSet1PackagesToDb(db);
    _addSet2PackagesToDb(db);
    _createRelationshipsForPkgs(db);

    Persistence<RepoPayload> persistence(db, "Project#1 Spring 2018");
    persistence.exportDb(db.keys(), "../db_shards/nosqldb_package_structure.xml");

    std::cout << "\n  project package structure has been saved to file" <<
        "'../db_shards/nosqldb_package_structure.xml'\n\n";

    setMessage("Generated package structure XML");
    return true;
}

bool test11b::operator()()
{
    using namespace NoSqlDb;

    DbCore<RepoPayload> db;
    Persistence<RepoPayload> persistence(db);

    persistence.importDb("../db_shards/nosqldb_package_structure.xml");

    std::cout << "\n  project package structure has been loaded from file" <<
        "'../db_shards/nosqldb_package_structure.xml'\n";

    showDb(db);
    std::cout << "\n\n";

    setMessage("Loaded package structure XML");
    return true;
}

//----< test stub >----------------------------------------------------

#ifdef TEST_PERSISTENCE

using namespace TestCore;

int main()
{
    TestSuite persistenceTestSuite("Testing Persistence - The Titans database");
    test8a test8a("Demonstrating Requirement #8a - persist to XML File");
    test8b test8b("Demonstrating Requirement #8b - restoring from XML File");
    test11a test11a("Demonstrating Requirement #11a - saving project package structure in XML format");
    test11b test11b("Demonstrating Requirement #11b - loading project package structure from the XML");
    persistenceTestSuite.registerEx(test8a);
    persistenceTestSuite.registerEx(test8b);
    persistenceTestSuite.registerEx(test11a);
    persistenceTestSuite.registerEx(test11b);

    persistenceTestSuite.executeAll();
}

#endif

