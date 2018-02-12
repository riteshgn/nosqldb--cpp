///////////////////////////////////////////////////////////////////////
// Query.cpp - Implements the query APIs                             //
// ver 1.3                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////

/*
* Maintenance History:
* --------------------
* ver 1.3 : 08 Feb 2018
* - pulled tests into the TestQuery.h file
* ver 1.2 : 07 Feb 2018
* - changes to API calls after introduction of QueryTypes
* ver 1.1 : 06 Feb 2018
* - added API definitions
* - added more tests
* ver 1.0 : 04 Feb 2018
* - first release
*/

#include "../Test/Test.h"
#include "TestQuery.h"

//----< test stub >----------------------------------------------------

using namespace Test;
using namespace NoSqlDbTests;


#ifdef TEST_QUERY

int main()
{
    TestSuite queryTestSuite("Testing Queries - The Titans database");
    test6 test6("Demonstrating Requirement #6 - simple querying");
    test7 test7("Demonstrating Requirement #7 - advanced querying");
    queryTestSuite.registerEx(test6);
    queryTestSuite.registerEx(test7);

    queryTestSuite.executeAll();
};

#endif // TEST_PERSISTENCE
