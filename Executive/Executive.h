#pragma once
///////////////////////////////////////////////////////////////////////
// Executive.h - Provides an executive interface                     //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: NoSqlDb, CSE687 - Object Oriented Design             //
// Author:      Ritesh Nair (rgnair@syr.edu)                         //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides interface definitions for Executor and Executive
* It also implements an Executor class to demonstrate the usage

* Required Files:
* ---------------
* NIL
*
* Maintenance History:
* --------------------
* ver 1.0 : 08 Feb 2018
* - first release
*/
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <functional>
#include <vector>

namespace Executive 
{
    /////////////////////////////////////////////////////////////////////
    // IExecutive interface
    // - defines the contract for all executives

    class IExecutive
    {
    public:
        virtual bool run() = 0;
    };

    /////////////////////////////////////////////////////////////////////
    // IExecutor interface
    // - defines the contract for all executors

    template <typename T>
    class IExecutor
    {
    public:
        virtual void registerEx(T& ex) = 0;
        virtual bool executeAll() const = 0;
    };

    /////////////////////////////////////////////////////////////////////
    // Executor class
    // - Implements the IExecutor interface to demonstrate its usage

    class Executor: public IExecutor<IExecutive>
    {
    public:
        // from: http://www.learncpp.com/cpp-tutorial/12-8-object-slicing/
        // "Essentially, std::reference_wrapper is a class that acts like a reference, 
        //  but also allows assignment and copying, so it’s compatible with std::vector."
        using Executives = std::vector<std::reference_wrapper<IExecutive>>;

    private:
        Executives executives_;

    public:
        void registerEx(IExecutive& ex) { executives_.push_back(ex); }
        bool executeAll() const;
    };
} // !Executive

#endif // !EXECUTIVE_H
