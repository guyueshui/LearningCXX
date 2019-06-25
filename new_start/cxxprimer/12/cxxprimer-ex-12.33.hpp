/******************************************************************************
* File:             cxxprimer-ex-12.32.hpp
*
* Author:           yychi  
* Created:          2019-06-25 21:10 
* Description:      Implemention of "cxxprimer-ex-12.32.h".
*****************************************************************************/

#include "cxxprimer-ex-12.32.h"

#include <sstream>
#include <algorithm>

TextQuery::TextQuery(std::ifstream& infile):
    Content(StrBlob()),
    WordLines(std::map<std::string, std::shared_ptr<std::set<LineNo>>>())
{
    LineNo line_num = 1;
    for (std::string line; std::getline(infile, line); ++line_num)
    {
        Content.push_back(line);
        std::istringstream is(line);

        for (std::string text, word; is >> text; word.clear())
        {
            std::remove_copy_if(text.begin(), text.end(),
                    std::back_inserter(word), ispunct);
            
            auto &lines = WordLines[word];
            if (!lines) lines.reset(new std::set<LineNo>);
            lines -> insert(line_num);
        }
    }
}

QueryResult TextQuery::query(const std::string& s) const
{
    static std::shared_ptr<std::set<LineNo>> nodata(new std::set<LineNo>);
    auto loc = WordLines.find(s);
    if (loc == WordLines.end())
        return QueryResult(s, nodata, Content);
    else
        return QueryResult(s, loc->second, Content);
}

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
    os << qr.target << " occurs " << qr.occurence()
        << (qr.occurence()>1 ? " times" : " time")
        << std::endl;
    for (auto num : *qr.pLines)
    {
        os << "\t(line " << num << ") "
            << qr.Content[num - 1]
            << std::endl;
    }
    return os;
}
