/******************************************************************************
* File:             cxxprimer-ex-15.4.cpp
*
* Author:           yychi  
* Created:          2019-07-03 20:50 
* Description:      Are the following declarations valid?
*****************************************************************************/

/**
 *  class Base { ... };
 *  (a) class Derived : public Derived { ... }  // invalid: can't derive itself
 *  (b) class Derived : private Base { ... }  // valid
 *  (c) class Derived : public Base;  // invalid, can't cover derive list
 */
