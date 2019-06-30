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
#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

// For convenience, i implement inside the class
class WordCounter {
public:
    WordCounter() = delete;
    WordCounter(std::ifstream& infile):
        WordCnts(unordered_map<string, size_t>())
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
    unordered_map<string, size_t> WordCnts;
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

/* here comes word transformation */
namespace word_trans {
// function declaration
unordered_map<string, string> buildMap(std::ifstream&);
const string& transform(const string&, const unordered_map<string, string>&);

// transform the in_file according to the map_file
void word_transform(std::ifstream& map_file, std::ifstream& in_file)
{
    auto trans_map = buildMap(map_file);
    for (string line; std::getline(in_file, line);)
    {
        std::istringstream is(line);
        bool FIRST = true;
        for (string word; is >> word;)
        {
            if (!FIRST) cout << " ";
            FIRST = false;
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

// build transform map from map_file
unordered_map<string, string> buildMap(std::ifstream& map_file)
{
    unordered_map<string, string> trans_map;
    for (string key, val; 
            map_file >> key && std::getline(map_file, val);)
    {
        if (val.size() > 1) // at least one effect character, " x" 
            trans_map[key] = val.substr(1); // remove the space ahead
        else
            throw std::runtime_error("no rule for " + key);
    }
    return trans_map;
}

// look up the word in the trans_map
const string& transform(const string& word,
                        const unordered_map<string, string>& trans_map)
{
    auto loc = trans_map.find(word);
    if (loc != trans_map.end())
        return loc -> second;
    else
        return word;
}
}

// test
int main(int argc, char *argv[])
{
    if (argc == 2) // run word counting
    {
        std::ifstream f(argv[1], std::istream::in);
        if (f)
            runQueries(f);
        else
        {
            std::cerr << "No such file";
            exit(1);
        }
    } else if (argc == 3) // run word transformation
    {
        std::ifstream map_file(argv[1]);
        std::ifstream in_file(argv[2]);
        if (map_file && in_file)
            word_trans::word_transform(map_file, in_file);
        else
        {
            std::cerr << "No such file";
            exit(1);
        }
    } else // print the usage
    {
        std::cerr << "Usage:\n";
        std::cerr << "- " << argv[0] << " file: for word counting\n";
        std::cerr << "- " << argv[0] 
            << " mapfile input: for word transformation";
        exit(1);
    }

    return 0;
}
