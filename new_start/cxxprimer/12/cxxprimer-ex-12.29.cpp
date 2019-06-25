/******************************************************************************
* File:             cxxprimer-ex-12.29.cpp
*
* Author:           yychi  
* Created:          2019-06-25 11:23 
* Description:      Use do while loops instead of while.
*****************************************************************************/

do {
    cout << "enter word to look for, or q to quit: ";
    string s;
    if (!(cin >> s) || s == "q") break;
    print(cout, tq.query(s)) << endl;
} while (true)

/** @IDEA
 *  As you like, I prefer "while" to "do while". 
 */

