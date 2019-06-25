/******************************************************************************
* File:             cxxprimer-ex-12.28.cpp
*
* Author:           yychi  
* Created:          2019-06-25 10:08 
* Description:      Implement text query procedure w/o using class.
*****************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using std::vector;
using std::string;
using std::map;
using std::set;
using std::shared_ptr;
using std::cout;
using std::endl;

using LineNo = vector<string>::size_type;

vector<string> Content; // loading file to a vector
map<string, set<LineNo>> WordLines; // word - occurence lines

void query(const string& filename)
{
    std::ifstream f(filename, std::ifstream::in);
    if (!f) throw std::runtime_error("No such file");

    LineNo line_num = 1;
    // initialize global variables
    for (string line; std::getline(f, line); ++line_num)
    {
        Content.push_back(line);
        std::istringstream is(line);
        for (string text, word; is >> text; word.clear())
        {
            std::remove_copy_if(text.begin(), text.end(),
                    std::back_inserter(word), ispunct);
            WordLines[word].insert(line_num);
        }
    }

    f.close(); // close file, no need anymore
    
    // perform the query
    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(std::cin >> s) || s == "q") break;
        else
        {
            const set<LineNo>& targetLines = WordLines[s];
            size_t occurence = targetLines.size();
            // print the query results
            cout << s << " occurs "
                << occurence << (occurence > 1 ? " times" : " time")
                << endl;
            for (auto id = targetLines.begin();
                    id != targetLines.end();
                    ++id)
            {
                cout << "(line " << *id << ") "
                    << Content[*id - 1] << endl;
            } 
        }
        cout << endl;
    }
} // query

// test
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        query(argv[1]);
    } else
        throw std::runtime_error("Need a filename");
    return 0;
}
