/******************************************************************************
* File:             cxxprimer-ex-12.30.hpp
*
* Author:           yychi  
* Created:          2019-06-25 15:24 
* Description:      Implemention of "cxxprimer-ex-12.30.h".
*****************************************************************************/

#include "cxxprimer-ex-12.30.h"

#include <sstream>
#include <algorithm>

/*** TextQuery ***/
TextQuery::TextQuery(std::ifstream& infile):
    pContents(std::make_shared<std::vector<std::string>>()),
    WordLines(std::map<std::string, std::shared_ptr<std::set<LineNo>>>())
{
    LineNo line_num = 1;
    for (std::string line; std::getline(infile, line); ++line_num)
    {
        pContents -> push_back(line);
        std::istringstream is(line);
        for (std::string text, word; is >> text; word.clear())
        {
            std::remove_copy_if(text.begin(), text.end(),
                    std::back_inserter(word), ispunct);
            
            auto &lines = WordLines[word];
            // allocate memory for smart ptrs
            if (!lines) lines.reset(new std::set<LineNo>);
            lines -> insert(line_num);
        }
    }
}

QueryResult TextQuery::query(const std::string& s) const
{
    // if not found
    static std::shared_ptr<std::set<LineNo>> nodata(new std::set<LineNo>);
    // use find to avoid add new key to the map
    auto loc = WordLines.find(s);
    if (loc == WordLines.end()) // not found
        return QueryResult(s, nodata, pContents);
    else
        return QueryResult(s, loc->second, pContents);
}
/*** end ***/

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
    os << qr.target << " occurs " << qr.occurence()
        << (qr.occurence()>1 ? " times" : " time")
        << std::endl;
    for (auto num : *qr.pLines)
    {
        os << "\t(line " << num << ") "
            << (*qr.pContents)[num - 1]
            << std::endl;
    }
    return os;
}
