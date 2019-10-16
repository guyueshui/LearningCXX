#include <iostream>
#include <cstring>

using namespace std;

char* ReplaceString(char* src, const char* pattern)
{
  int plen = strlen(pattern);
  char* s = src;
  for (; *(s + plen) != '\0';)
  {
    bool is_match = true;
    const char *p = pattern;
    for (char* beg = s; *p != '\0';)
    {
      if (std::isspace(*p))
      {
        ++beg;
        ++p;
      }
      else
      {
        if (*beg != *p)
        {
          is_match = false;
          break;
        }
      }
    }

    if (is_match)
    {
      for (const char* p = pattern; *p != '\0'; ++p)
      {
        if (!std::isspace(*p))
        {
          *s = '*';
        }
        ++s;
      }
    }
    else
    {
      ++s;
    }
  }
  return src;
}
