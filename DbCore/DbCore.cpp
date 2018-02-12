///////////////////////////////////////////////////////////////////////
// DbCore.cpp - Implements NoSql database prototype                  //
// ver 1.3                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair                                          //
///////////////////////////////////////////////////////////////////////

/*
* Maintenance History:
* --------------------
* ver 1.3 : 9 Feb 2018
* - pulled out all the test function into the TesDbCore.h file
* ver 1.2 : 4 Feb 2018
* - added tests for requirements 3 and 4
*   i.e. addition/removal of key/values and editing of values
* ver 1.1 : 2 Feb 2018
* - fixed tests to accomodate the changes to DbElement class & introduction of DbElementMetadata class
* ver 1.0 : 10 Jan 2018
* - first release
*/

#include "../Test/Test.h"
#include "TestDbCore.h"

//----< test stub >----------------------------------------------------

using namespace Test;
using namespace NoSqlDbTests;

#ifdef TEST_DBCORE

int main()
{
    TestSuite dbCoreTestSuite("Testing DbCore - He said, she said database");
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

    dbCoreTestSuite.executeAll();
}
#endif
