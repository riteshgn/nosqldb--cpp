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
* ver 1.0 : 09 Feb 2018
* - first release
*/

#include "../Test/Test.h"
#include "TestRepoPayload.h"

//----< test stub >----------------------------------------------------

using namespace Test;
using namespace NoSqlDbTests;

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

