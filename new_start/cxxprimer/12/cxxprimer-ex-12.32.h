/******************************************************************************
* File:             cxxprimer-ex-12.32.h
*
* Author:           yychi  
* Created:          2019-06-25 21:29 
* Description:      Rewrite "TextQuery" and "QueryResult" using "StrBlob".
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
    QueryResult(const std::string& t,
                std::shared_ptr<std::set<TextQuery::LineNo>> l,
                const StrBlob& c):
        target(t), pLines(l), Content(c) { }
    size_t occurence() const { return pLines -> size(); } 
private:
    std::string target;
    std::shared_ptr<std::set<TextQuery::LineNo>> pLines;
    StrBlob Content;
};

#endif /* ifndef QUERY_H */
