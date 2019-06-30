/******************************************************************************
* File:             cxxprimer-ex-11.33.cpp
*
* Author:           yychi  
* Created:          2019-06-30 10:50 
* Description:      Write your own word transform procedure.
*****************************************************************************/

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using std::map;
using std::string;
using std::cout;
using std::endl;

map<string, string> buildMap(std::ifstream&);
const string& transform(const string&, const map<string, string>&);

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
map<string, string> buildMap(std::ifstream& map_file)
{
    map<string, string> trans_map;
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
                        const map<string, string>& trans_map)
{
    auto loc = trans_map.find(word);
    if (loc != trans_map.end())
        return loc -> second;
    else
        return word;
}

// test
int main(int argc, char *argv[])
{
    if (argc == 3) // argv[0], argv[1], argv[2]
    {
        std::ifstream fin(argv[1]);
        std::ifstream fmap(argv[2]);
        if (fin && fmap)
            word_transform(fmap, fin);
        else
        {
            std::cerr << "No such file";
            exit(1);
        }
    } else
    {
        std::cerr << "Usage: " << argv[0] << " input map";
        exit(1);
    }
    return 0;
}

/** @best practice?
 *  - Use exit(__status__) in main
 *  - Use throw in your module
 */

