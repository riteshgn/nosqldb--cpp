///////////////////////////////////////////////////////////////////////
// Test.cpp - Implements the Test Executor                           //
// ver 1.2                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////

/*
* Maintenance History:
* --------------------
* ver 1.0 : 08 Feb 2018
* - first release
*/

#include "Test.h"
#include "../DbCore/TestDbCore.h"
#include "../Query/TestQuery.h"
#include "../Persistence/TestPersistence.h"
#include "../Payloads/TestRepoPayload.h"

#include <iostream>

using namespace Test;
using namespace NoSqlDbTests;

void showMessageForOtherRequirements()
{
    Console::setConsoleColor(Console::COLOR_PURPLE);
    Utilities::Title("Other non-functional requirements");
    Console::setConsoleColor(Console::COLOR_WHITE);

    Console::setConsoleColor(Console::COLOR_GREY);
    Utilities::title("Demonstrating Requirement #10");
    Console::setConsoleColor(Console::COLOR_WHITE);

    std::cout << "\n  A visual examination of all the submitted code will show the " <<
        "use of Executive, DbCore, Query & Test packages along with Persistence and DbPayloads packages. \n\n";

    Console::setConsoleColor(Console::COLOR_GREEN);
    std::cout << "\n    Test Passed - \"Use of packages\"\n\n";
    Console::setConsoleColor(Console::COLOR_WHITE);

    Console::setConsoleColor(Console::COLOR_GREY);
    Utilities::title("Demonstrating Requirement #12");
    Console::setConsoleColor(Console::COLOR_WHITE);

    std::cout << "\n  The execution of these Test Suites proves the working of the Test executive.\n\n";

    Console::setConsoleColor(Console::COLOR_GREEN);
    std::cout << "\n    Test Passed - \"Test executive\"\n\n";
    Console::setConsoleColor(Console::COLOR_WHITE);

    Console::setConsoleColor(Console::COLOR_GREY);
    Utilities::title("Demonstrating Requirement #13");
    Console::setConsoleColor(Console::COLOR_WHITE);

    std::cout << "\n  The package diagram can be found in the root of the project folder " <<
        "[../package_diagram.pdf]\n\n";

    Console::setConsoleColor(Console::COLOR_GREEN);
    std::cout << "\n    Test Passed - \"Package diagram\"\n\n";
    Console::setConsoleColor(Console::COLOR_WHITE);
}

//----< test stub >----------------------------------------------------

#ifdef TEST_ALL

int main()
{
    TestSuite dbCoreTestSuite("Testing DbCore - He said, she said database / The Titans database");
    test1 test1("Demonstrating Requirement #1");
    test2 test2("Demonstrating Requirement #2");
    test3a test3a("Demonstrating Requirement #3a - creating DbElement");
    test3b test3b("Demonstrating Requirement #3b - creating DbCore");
    test4a test4a("Demonstrating Requirement #4a - adding key/value pairs to DB");
    test4b test4b("Demonstrating Requirement #4b - removing key/value pairs from DB");
    test5a test5a("Demonstrating Requirement #5a - adding relationships");
    test5b test5b("Demonstrating Requirement #5b - removing relationships");
    test5c test5c("Demonstrating Requirement #5c - editing metadata");
    test5d test5d("Demonstrating Requirement #5d - replacing the payload");
    dbCoreTestSuite.registerEx(test1);
    dbCoreTestSuite.registerEx(test2);
    dbCoreTestSuite.registerEx(test3a);
    dbCoreTestSuite.registerEx(test3b);
    dbCoreTestSuite.registerEx(test4a);
    dbCoreTestSuite.registerEx(test4b);
    dbCoreTestSuite.registerEx(test5a);
    dbCoreTestSuite.registerEx(test5b);
    dbCoreTestSuite.registerEx(test5c);
    dbCoreTestSuite.registerEx(test5d);
    TestSuite queryTestSuite("Testing Queries - The Titans database");
    test6 test6("Demonstrating Requirement #6 - simple querying");
    test7 test7("Demonstrating Requirement #7 - advanced querying");
    queryTestSuite.registerEx(test6);
    queryTestSuite.registerEx(test7);
    TestSuite persistenceTestSuite("Testing Persistence - The Titans database");
    test8a test8a("Demonstrating Requirement #8a - persist to XML File");
    test8b test8b("Demonstrating Requirement #8b - restoring from XML File");
    persistenceTestSuite.registerEx(test8a);
    persistenceTestSuite.registerEx(test8b);
    TestSuite repoPayloadTestSuite("Testing Custom Payload - The Repository database");
    test9 test9("Demonstrating Requirement #9 - custom payload");
    repoPayloadTestSuite.registerEx(test9);
    TestSuite packageStructureTestSuite("Testing Package Structure");
    test11a test11a("Demonstrating Requirement #11a - creating an XML with package structure");
    test11b test11b("Demonstrating Requirement #11b - loading the package structure XML to DB");
    packageStructureTestSuite.registerEx(test11a);
    packageStructureTestSuite.registerEx(test11b);

    TestExecutor executor;
    executor.registerEx({ dbCoreTestSuite, queryTestSuite, persistenceTestSuite,
        repoPayloadTestSuite, packageStructureTestSuite });
    executor.executeAll();

    showMessageForOtherRequirements();
    return 0;
}

#endif // TEST_ALL