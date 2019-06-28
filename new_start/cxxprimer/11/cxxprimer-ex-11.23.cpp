/******************************************************************************
* File:             cxxprimer-ex-11.7.cpp
*
* Author:           yychi  
* Created:          2019-06-26 22:11 
* Description:      Define a multimap, whose key is the family name and value is
*                   a vector of children's name. Implement a methods to add
*                   new family and add new child to exist family.
*****************************************************************************/

#include <map>
#include <string>
#include <vector>
#include <iostream>

using std::multimap;
using std::vector;
using std::string;

class Families {
public:
    Families(): FamChs(multimap<string, vector<string>>()) { }
    // add new family
    void addFamily(const string& famname)
    {
        FamChs.insert({famname, vector<string>()});
    }
    // add new child
    void addChild(const string& childname, const string& famname)
    {
        auto loc = FamChs.find(famname);
        if (loc != FamChs.end())
            (loc -> second).push_back(childname);
        else
            throw std::runtime_error("No such family");
    }

    void printer()
    {
        for (auto &f : FamChs)
        {
            std::cout << f.first << ": ";
            for (auto &c : f.second)
                std::cout << c << " ";
            std::cout << std::endl;
        }
    }
private:
    multimap<string, vector<string>> FamChs;
};

// test
int main()
{
    Families f;
    f.addFamily("Luis");
    f.addChild("Saido", "Luis");
    // f.addChild("Linus", "Tornards");
    f.addFamily("John");
    f.addChild("Michael", "John");
    // f.addChild("Zero", "Luis");
    f.printer();
    return 0;
}
