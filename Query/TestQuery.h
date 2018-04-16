#pragma once
///////////////////////////////////////////////////////////////////////
// TestQuery.h - Implements all test cases for Query                 //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This file implements the test functors for testing Query

* Required Files:
* ---------------
* Query.h, Query.cpp
* NoSqlDbTests.h
*
* Maintenance History:
* --------------------
* ver 1.1 : 15 Apr 2018
* - Moved implementation into cpp file
* ver 1.0 : 08 Feb 2018
* - first release
*/

#ifndef TEST_QUERY_H
#define TEST_QUERY_H

#include "../TestCore/TestCore.h"
#include "../DbCore/DbCoreTestHelper.h"

namespace NoSqlDbTests {
    
    /////////////////////////////////////////////////////////////////////
    // test functors
    // - Implements test cases to demonstrate the various requirements 
    //   on Persistence module

    class test6 : public TestCore::AbstractTest {
    public:
        test6(TestCore::AbstractTest::TestTitle title): TestCore::AbstractTest(title) {  }
        virtual bool operator()(); 
    private:
        bool _executePart1(NoSqlDb::DbCore<std::string>& db);
        bool _executePart2(NoSqlDb::DbCore<std::string>& db);
    };
    class test7 : public TestCore::AbstractTest {
    public:
        test7(TestCore::AbstractTest::TestTitle title) : TestCore::AbstractTest(title) {  }
        virtual bool operator()(); 
    private:
        bool _executePart1(NoSqlDb::DbCore<std::string>& db);
        bool _executePart2(NoSqlDb::DbCore<std::string>& db);
    };

}

#endif // !TEST_QUERY_H