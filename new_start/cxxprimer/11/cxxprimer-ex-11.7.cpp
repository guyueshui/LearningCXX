/******************************************************************************
* File:             cxxprimer-ex-11.7.cpp
*
* Author:           yychi  
* Created:          2019-06-26 22:11 
* Description:      Define a map, whose key is the family name, and value is
*                   a vector of children's name. Implement a methods to add
*                   new family and add new child to exist family.
*****************************************************************************/

#include <map>
#include <string>
#include <vector>
#include <iostream>

using std::map;
using std::vector;
using std::string;

class Families {
public:
    Families(): FamChs(map<string, vector<string>>()) { }
    // add new family
    void addFamily(const string& famname)
    {
        FamChs[famname] = vector<string>();
    }
    // add new child
    void addChild(const string& childname, const string& famname)
    {
        FamChs[famname].push_back(childname);
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
    map<string, vector<string>> FamChs;
};

// test
int main()
{
    Families f;
    f.addFamily("Luis");
    f.addChild("Saido", "Luis");
    f.addChild("Linus", "Tornards");
    f.addFamily("John");
    f.addChild("Michael", "John");
    f.addChild("Zero", "Luis");
    f.printer();
    return 0;
}
