///////////////////////////////////////////////////////////////////////
// Persistence.cpp - Implements the persistence APIs                 //
// ver 1.2                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////

/*
* Maintenance History:
* --------------------
* ver 1.2 : 08 Feb 2018
* - pulled tests into the TestPersistence.h file
* ver 1.1 : 06 Feb 2018
* - added modifications required for interface change
* - added more checks in tests
* ver 1.0 : 05 Feb 2018
* - first release
*/

#include "../Test/Test.h"
#include "TestPersistence.h"

//----< test stub >----------------------------------------------------

using namespace Test;
using namespace NoSqlDbTests;

#ifdef TEST_PERSISTENCE

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

