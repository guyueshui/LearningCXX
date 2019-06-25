/******************************************************************************
* File:             cxxprimer-ex-12.32.h
*
* Author:           yychi  
* Created:          2019-06-25 21:29 
* Description:      Rewrite "TextQuery" and "QueryResult", add members to
*                   return iterators of the set of line numbers, and a
*                   member "get_file" returns a shared_ptr points to the
*                   file content of "QueryResult".
*****************************************************************************/

#ifndef QUERY_H
#define QUERY_H

#include "StrBlob.hpp"

#include <fstream>
#include <set>
#include <map>

class QueryResult; // declaration
class TextQuery {
public:
    using LineNo = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&); 
    QueryResult query(const std::string&) const;
private:
    StrBlob Content;
    std::map<std::string, std::shared_ptr<std::set<LineNo>>> WordLines;
};

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    using ResIter = std::set<TextQuery::LineNo>::iterator;

    QueryResult(const std::string& t,
                std::shared_ptr<std::set<TextQuery::LineNo>> l,
                const StrBlob& c):
        target(t), pLines(l), Content(c) { }
    size_t occurence() const { return pLines -> size(); } 

    // added APIs
    std::shared_ptr<StrBlob> get_file() const 
    {
        return std::make_shared<StrBlob>(Content);
    }
    ResIter begin() const { return pLines -> begin(); }
    ResIter end() const { return pLines -> end(); }
private:
    std::string target;
    std::shared_ptr<std::set<TextQuery::LineNo>> pLines;
    StrBlob Content;
};

#endif /* ifndef QUERY_H */
