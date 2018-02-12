#pragma once
///////////////////////////////////////////////////////////////////////
// Test.h - Implements the Test Executive framework for NoSqlDb      //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides an interface and its implementation:
* - IPersistence interface defines the behavior to be implemented by Persistence providers.
* - Persistence is an implementation of IPersistence interface which, as per the contract,
provides an API to exports selected DB records to a file. It also provides an API to
restore/augment DB records from a file.

* Required Files:
* ---------------
* Executive.h, Executive.cpp
* StringUtilities.h, StringUtilities.cpp
* XmlDocument.h, XmlDocument.cpp
* DateTime.h, DateTime.cpp
* Console.h
*
* Maintenance History:
* --------------------
* ver 1.1 : 10 Feb 2018
* - added console colors for highlighting output
* - handling exceptions so that the executor can complete the full cycle
* ver 1.0 : 08 Feb 2018
* - first release
*/

#ifndef TEST_H
#define TEST_H

#include "../Executive/Executive.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../ConsoleColor/ConsoleColor.h"

#include <string>

using namespace Executive;

namespace Test {

    /////////////////////////////////////////////////////////////////////
    // AbstractTest functor
    // - defines the contract for all test functors
    // - implements helper apis for getting the test title and 
    //   setting/getting the message which indicates the status of a test.

    class AbstractTest
    {
    public:
        using TestMsg = std::string;
        using TestTitle = std::string;
        virtual bool operator()() = 0;
        TestMsg getTestTitle() { return title_; };
        TestMsg getMessage() { return msg_; };
        void setMessage(TestMsg msg) { msg_ = msg; };

    protected:
        AbstractTest(TestTitle title) : title_(title) {};

    private:
        TestTitle title_;
        TestMsg msg_ = "";
    };

    /////////////////////////////////////////////////////////////////////
    // TestSuite class
    // - implements the IExecutor interface
    // - stores a collection of test functors and executes them when invoked

    class TestSuite : public IExecutor<AbstractTest>
    {
    public:
        using SuiteTitle = std::string;
        using TestFunctions = std::vector<std::reference_wrapper<AbstractTest>>;

        TestSuite(SuiteTitle title) : title_(title) {};

        SuiteTitle getTitle() { return title_; };
        virtual void registerEx(AbstractTest& test) { tests_.push_back(test); };
        void registerEx(TestFunctions tests);
        virtual bool executeAll() const;

    private:
        TestFunctions tests_;
        SuiteTitle title_;
    };

    /////////////////////////////////////////////////////////////////////
    // TestExecutor class
    // - implements the IExecutor interface
    // - stores a collection of test suites and executes them when invoked

    class TestExecutor : public IExecutor<TestSuite>
    {
    public:
        using TestSuites = std::vector<std::reference_wrapper<TestSuite>>;

        virtual void registerEx(TestSuite& suite) { suites_.push_back(suite); };
        void registerEx(TestSuites suites);
        virtual bool executeAll() const;

    private:
        TestSuites suites_;
    };

    // Test Helper functions

    //----< reduce the number of characters to type >----------------------

    auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
    {
        Utilities::putline(n, out);
    };

    /////////////////////////////////////////////////////////////////////
    // TestExecutor methods

    //----< convenience function for registering a list of test suites >---------------------

    void TestExecutor::registerEx(TestSuites suites)
    {
        for (TestSuite& suite : suites)
        {
            registerEx(suite);
        }
    }

    //----< executes all test suites and return true if all of them pass >---------------------

    bool TestExecutor::executeAll() const
    {
        bool executorResult = true;
        for (TestSuite& suite : suites_)
        {
            Console::setConsoleColor(Console::COLOR_PURPLE);
            Utilities::Title(suite.getTitle());
            Console::setConsoleColor(Console::COLOR_WHITE);
            putLine();

            if (!suite.executeAll())
                executorResult = false;
        }

        if (executorResult)
        {
            Console::setConsoleColor(Console::COLOR_GREEN);
            std::cout << "\n    All Test Suites have PASSED... \n\n";
        }
        else
        {
            Console::setConsoleColor(Console::COLOR_RED);
            std::cout << "\n    Atleast one of the Test Suites has FAILED... \n\n";
        }

        Console::setConsoleColor(Console::COLOR_WHITE);
        return executorResult;
    }

    /////////////////////////////////////////////////////////////////////
    // TestSuite methods

    //----< convenience function for registering a list of test functors >---------------------

    void TestSuite::registerEx(TestFunctions tests)
    {
        for (AbstractTest& test : tests)
        {
            registerEx(test);
        }
    }

    //----< executes all test functors and return true if all of them pass >---------------------

    bool TestSuite::executeAll() const
    {
        bool suiteResult = true;
        for (AbstractTest& test : tests_)
        {
            Console::setConsoleColor(Console::COLOR_GREY);
            Utilities::title(test.getTestTitle());
            Console::setConsoleColor(Console::COLOR_WHITE);

            bool result = false;
            try 
            {
                result = test();
            }
            catch (std::exception &exception)
            {
                std::string expStr = exception.what();
                test.setMessage("Exception: " + expStr);
            }
            catch (...)
            {
                test.setMessage("Unexpected error occured...");
            }

            std::string resultStr = "PASSED";
            if (result)
            {
                Console::setConsoleColor(Console::COLOR_GREEN);
            }
            else
            {
                Console::setConsoleColor(Console::COLOR_RED);
                resultStr = "FAILED";
            }

            std::cout << "\n    Test " << resultStr << " - \"" << test.getMessage() << "\"\n\n";

            if (!result)
                suiteResult = false;

            Console::setConsoleColor(Console::COLOR_WHITE);
        }

        return suiteResult;
    }

} // ! -- ns:Test

#endif // !TEST_H