/******************************************************************************
* File:             cxxprimer-ex-15.8.cpp
*
* Author:           yychi  
* Created:          2019-07-04 21:57 
* Description:      Give the definition of static type and dynamic type.
*****************************************************************************/

/** @IDEA
 *  - static type: known when compiling
 *  - dynamic type: known at runtime
 */

/* ex-15.9 */
/** @IDEA
 *  The static type of a pointer or reference to base class may differ from
 *  its dynamic type.
 *  e.g.:
 *      class A;
 *      class B : public A {};
 *      B b;
 *      A* pa = &b;
 *      A& ra = b;
 *      A a = b;
 */

/* ex-15.10 */
/** @IDEA
 *  Since "ifstream" is-a "istream", we can use derived class object whenever 
 *  there needs a base class object.
 */

