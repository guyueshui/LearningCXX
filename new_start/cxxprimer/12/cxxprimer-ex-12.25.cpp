/******************************************************************************
* File:             cxxprimer-ex-12.25.cpp
*
* Author:           yychi  
* Created:          2019-06-24 18:54 
* Description:      Given the expression, how will you release the pointer?
*****************************************************************************/

int main()
{
    int *pa = new int[10];
    delete [] pa; // just delete, don't forget []
    return 0;
}
