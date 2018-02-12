///////////////////////////////////////////////////////////////////////
// Persistence.cpp - Implements the executor APIs                    //
// ver 1.0                                                           //
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

#include "Executive.h"

#include <iostream>

using namespace Executive;

/////////////////////////////////////////////////////////////////////
// Executor methods

//----< runs all the executives and returns the result >---------------------

bool Executor::executeAll() const
{
    for (IExecutive& executive : executives_)
    {
        executive.run();
    }
    return true;
}

//----< implements a dummy executive for testing >---------------------

class ExampleExecutive1 : public IExecutive
{
    virtual bool run()
    {
        std::cout << "\nExecuting 1...\n";
        return true;
    }
};

//----< implements a dummy executive for testing  >---------------------

class ExampleExecutive2 : public IExecutive
{
    virtual bool run()
    {
        std::cout << "\nExecuting 2...\n";
        return true;
    }
};

//----< test stub >----------------------------------------------------

#ifdef TEST_EXECUTIVE

int main()
{
    Executor executor;

    ExampleExecutive1 eex1;
    IExecutive& ex1 = eex1;

    ExampleExecutive2 eex2;
    IExecutive& ex2 = eex2;

    executor.registerEx(ex1);
    executor.registerEx(ex2);

    executor.executeAll();

    return 0;
}

#endif // TEST_EXECUTIVE