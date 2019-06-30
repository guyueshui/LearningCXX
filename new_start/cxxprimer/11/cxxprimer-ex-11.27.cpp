/******************************************************************************
* File:             cxxprimer-ex-11.27.cpp
*
* Author:           yychi  
* Created:          2019-06-29 22:55 
* Description:      When will you use "count", when "find"?
*****************************************************************************/

/** @IDEA
 *  As it says, count aimed to count the number of equivalent keys, while find
 *  is to find the position of the give key.
 */

/* ex-11.28 */

map<string, vector<int>> m;
map<string, vector<int>::iterator loc = m.find("haha");

/* ex-11.29 */

/** @IDEA
 *  For a given key that is not in the container c,
 *  - upper_bound returns a safe insert point, which don't affect the order
 *    of origin keys
 *  - lower_bound returns the same insert point as upper_bound
 *  - equal_range returns a pair of {c.end(), c.end()}
 */

/* ex-11.30 */

/** @IDEA
 *  pos is a pair of iterator
 *  pos.first is an iterator
 *  pos.first -> second is the mapped value
 */

