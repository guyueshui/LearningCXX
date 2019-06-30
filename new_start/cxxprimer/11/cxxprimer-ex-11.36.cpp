/******************************************************************************
* File:             cxxprimer-ex-11.36.cpp
*
* Author:           yychi  
* Created:          2019-06-30 15:12 
* Description:      Our program deosn't check the input file. What if there
*                   exists a line
*                       "u "
*                   like this?
*****************************************************************************/

/** @IDEA
 *  If there exists such line, it will complain
 *      "no rule for u"
 *  and the buildMap will failed, the whole program aborted.
 *
 *  I had verified at ex-11.33.
 */

