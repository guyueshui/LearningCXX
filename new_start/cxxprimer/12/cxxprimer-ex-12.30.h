/******************************************************************************
* File:             cxxprimer-ex-12.30.h
*
* Author:           yychi  
* Created:          2019-06-25 14:59 
* Description:      Implement "TextQuery" and "QueryResult" after further
*                   reading of book.
*****************************************************************************/

#ifndef QUERY_H
#define QUERY_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <fstream>

class QueryResult; // declaration
class TextQuery {
public:
    using LineNo = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const; 
private:
    // file contents
    std::shared_ptr<std::vector<std::string>> pContents;
    // word - lines map
    std::map<std::string, std::shared_ptr<std::set<LineNo>>> WordLines;
};

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    QueryResult(const std::string& t, 
                std::shared_ptr<std::set<TextQuery::LineNo>> l,
                std::shared_ptr<std::vector<std::string>> c):
        target(t), pLines(l), pContents(c) { } 
    // the target word occurence
    size_t occurence() const { return pLines -> size(); }
private:
    std::string target; // word to query
    std::shared_ptr<std::set<TextQuery::LineNo>> pLines; // occurs in lines
    std::shared_ptr<std::vector<std::string>> pContents;
};

#endif /* ifndef QUERY_H */
