#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* rand_str(char* str, const int len)
{
  srand(time(NULL));
  for (int i = 0; i < len; ++i)
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


int main()
{
    int len = 10;
    char* str = new char[len + 1];
    printf("%s\n", rand_str(str, len));
    delete[] str;
    return 0;
}
