///////////////////////////////////////////////////////////////////////
// RepoPayload.cpp - Implements the persistence APIs                 //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////

/*
* Maintenance History:
* --------------------
* ver 1.1 : 15 Apr 2018
* - Added tests
* ver 1.0 : 09 Feb 2018
* - first release
*/

#include "RepoPayload.h"
#include "../Query/Query.h"
#include "TestRepoPayload.h"
#include "../DbCore/DbCoreTestHelper.h"

using namespace NoSqlDbTests;

// test functions

class CategoryHeader : public NoSqlDb::IPayloadSearchCriteria<Repository::RepoPayload>
{
    virtual bool operator()(const Repository::RepoPayload& payload);
};

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

bool CategoryHeader::operator()(const Repository::RepoPayload& payload)
{
    using Category = std::string;
    for (Category category : payload.categories())
    {
        if (category == "Header")
            return true;
    }
    return false;
}

//----< demo custom payload requirement #9 >---------------------
bool test9::operator()()
{
    using namespace NoSqlDb;
    using namespace Repository;

    DbCore<RepoPayload> db;
    DbTestHelper::showInitialDbState(db);

    _populateTestData(db);
    if (db.size() != 4)
    {
        setMessage("Expected db to have 4 elements");
        return false;
    }

    std::cout << "\n  after adding elements with keys: ";
    DbCore<RepoPayload>::Keys keys = db.keys();
    showKeys(db);
    std::cout << "\n";

    std::cout << "\n  make all header files children of respective cpp files";
    db["DateTime.cpp"].addRelationship("DateTime.h");
    db["DbCore.cpp"]
        .addRelationship("Date.h")
        .addRelationship("DbCore.h");

    std::cout << "\n\n  showing all the database elements:";
    showDb(db);
    std::cout << "\n";

    Query<RepoPayload> query;
    CategoryHeader categoryHeader;
    DbCore<RepoPayload> result = query.from(db).where.payload.has(categoryHeader).end();

    std::cout << "\n\n  Demonstrating custom payload query: ";
    std::cout << "\n  code> query.from(db).where.payload.has(categoryHeader).end()\n";
    showDb(result);
    std::cout << "\n";

    /*Persistence<RepoPayload> persistence(db);
    persistence.exportDb(db.keys(), "../db_shards/test_repopayload.xml");*/

    // clean up and return
    std::cout << "\n\n";

    setMessage("Adding custom payload to NoSQlDb");
    return true;
}


//----< test stub >----------------------------------------------------

using namespace TestCore;

#ifdef TEST_DBPAYLOADS

int main()
{
    TestSuite repoPayloadTestSuite("Testing Queries - The Titans database");
    test9 test9("Demonstrating Requirement #9 - custom payload");
    repoPayloadTestSuite.registerEx(test9);

    repoPayloadTestSuite.executeAll();

    return 0;
}

#endif // TEST_DBPAYLOADS

