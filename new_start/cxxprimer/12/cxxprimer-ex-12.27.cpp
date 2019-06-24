/******************************************************************************
* File:             cxxprimer-ex-12.27.cpp
*
* Author:           yychi  
* Created:          2019-06-24 20:17 
* Description:      Implement your "TextQuery" and "QueryResult" class.
*****************************************************************************/

#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>

class TextQuery; // declaration
class QueryResult {
public:
    QueryResult(const TextQuery&, const std::string&);
    void print() const; // print the query result
private:
    std::string target; // the word queried
    std::shared_ptr<std::vector<std::string>> pContent;
    std::shared_ptr<std::map<std::string, std::set<size_t>>> pWord_lines;
    size_t occurence() const; // the occurence of the target word
};

class TextQuery {
    // QueryResult need to access private members
    friend QueryResult::QueryResult(const TextQuery&, const std::string&);
public:
    TextQuery(std::ifstream&); // construct from a fstream
    QueryResult query(const std::string&); // query the given word
    void printer()
    {
        for (auto &e: *pContent)
            std::cout << e << std::endl;
        for (auto iter = pWord_lines->begin();
                iter != pWord_lines->end();
                ++iter)
        {
            std::cout << "{" << iter->first
                << ", " << iter->second.size()
                <<  "}" << std::endl;
        }
    }
private:
    // use dynamic allocated memory for object sharing
    std::shared_ptr<std::vector<std::string>> pContent;
    std::shared_ptr<std::map<std::string, std::set<size_t>>> pWord_lines;
};

#endif /* ifndef QUERY_ */

/*** impl of TextQuery ***/
TextQuery::TextQuery(std::ifstream& infile):
    pContent(std::make_shared<std::vector<std::string>>()),
    pWord_lines(std::make_shared
            <
            std::map<std::string, std::set<size_t>>
            >())
{
    std::string line, word;
    size_t line_num = 1;
    while (std::getline(infile, line))
    {
        pContent -> push_back(line);
        std::istringstream is(line);
        // for each line, build the map
        while (is >> word)
        {
            (*pWord_lines)[word].insert(line_num);
        }
        ++line_num;
    }
}

QueryResult TextQuery::query(const std::string& word)
{
    QueryResult ret(*this, word);
    return ret;
}
/*** end ***/

/*** impl of QueryResult ***/
QueryResult::QueryResult(const TextQuery& tq, const std::string& word):
    target(word), 
    pContent(tq.pContent),
    pWord_lines(tq.pWord_lines) { }

size_t QueryResult::occurence() const
{
    return (*pWord_lines)[target].size();
}

void QueryResult::print() const
{
    std::cout << target << " occurs "
        << occurence() << " times\n";
    auto *pSet = &((*pWord_lines)[target]); // may crash?
    for (auto id = pSet->begin(); id != pSet->end(); ++id)
    {
        std::cout << "   (line "
            << *id << ") "
            << pContent -> at(*id - 1)
            << std::endl;
    }
}
/*** end ***/
std::ostream& print(std::ostream& os, const QueryResult& qr)
{
    qr.print();
    return os;
}

void runQueries(std::ifstream& infile)
{
    TextQuery tq(infile);
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
    }
}

// test
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::ifstream infile(argv[1], std::ifstream::in);
        // TextQuery tq(infile);
        // tq.printer(); 
        // tq.query("StrBlob").print();
        runQueries(infile);
    } else
        throw std::invalid_argument("Need a filename");
    return 0;
}
