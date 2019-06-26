/******************************************************************************
* File:             cxxprimer-ex-11.3.cpp
*
* Author:           yychi  
* Created:          2019-06-26 21:10 
* Description:      Write your own word count procedure.
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

// For convenience, i implement inside the class
class WordCounter {
public:
    WordCounter() = delete;
    WordCounter(std::ifstream& infile):
        WordCnts(map<string, size_t>())
    {
        for (string line; std::getline(infile, line);)
        {
            std::istringstream is(line);
            for (string word; is >> word;)
                WordCnts[word]++;
        }
    }
    size_t query(const string& target)
    {
        return WordCnts[target];
    }
private:
    map<string, size_t> WordCnts;
};

void runQueries(std::ifstream& infile)
{
    WordCounter wc(infile);
    while (true)
    {
        cout << "enter a word to query, or q to quit: ";
        string s;
        if (!(std::cin >> s) || s == "q") break;
        cout << s << " occurs "
            << wc.query(s)
            << (wc.query(s) > 1 ? " times" : " time")
            << endl;
    }
}

// test
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        std::ifstream f(argv[1], std::istream::in);
        if (f)
            runQueries(f);
        else
            throw std::runtime_error("No such file");
    } else
        throw std::invalid_argument("Need a filename");
    return 0;
}
