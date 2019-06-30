/******************************************************************************
* File:             cxxprimer-ex-11.34.cpp
*
* Author:           yychi  
* Created:          2019-06-30 15:07 
* Description:      What if use member find instead of transform?
*****************************************************************************/

/** @IDEA
 *  If the given key isn't found, you may dereference a end iterator, which
 *  is undefined behaviour.
 */

/* ex-11.35 */
/** @IDEA
 *  If a key occurs multiple times,
 *      - trans_map[key] = value.substr(1) will update it to the last occurence
 *        of its value
 *      - trans_map.insert({key, value.substr(1)}) will use the first occurenece
 *        of its value
 */

