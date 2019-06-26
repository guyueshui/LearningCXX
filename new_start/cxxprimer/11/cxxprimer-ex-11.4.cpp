/******************************************************************************
* File:             cxxprimer-ex-11.4.cpp
*
* Author:           yychi  
* Created:          2019-06-26 21:10 
* Description:      Write your own word count procedure, provide more robust
*                   word recognition: ignore cases, punctuations.
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
            for (string text, word; is >> text; word.clear())
            {
                // ignore punctuations
                std::remove_copy_if(text.begin(), text.end(),
                        std::back_inserter(word), ispunct);

                // transform the word to lowercase
                // see: https://en.cppreference.com/w/cpp/string/byte/tolower
                std::transform(word.begin(), word.end(), word.begin(),
                        [](unsigned char c){ return std::tolower(c); });

                WordCnts[word]++;
            }
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
