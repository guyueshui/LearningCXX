#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

namespace utils {

char* rand_str(char* str, const size_t len)
{
  srand(time(NULL));
  for (size_t i = 0; i < len; ++i)
  {
    switch (rand() % 3)
    {
      case 1: str[i] = 'A' + rand() % 26; break;
      case 2: str[i] = 'a' + rand() % 26; break;
      default: str[i] = '0' + rand() % 10; break;
    }
  }
  // NOTE: please ensure @str[len] is in valid memory range.
  str[len] = '\0'; // terminate flag
  return str;
}

} // namespace utils