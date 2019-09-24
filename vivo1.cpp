#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stack>

using namespace std;

/**
 * Welcome to vivo !
 */
 
int solution(int a[], int N)
{
  if (N == 0) return -1;
  
  int cnt = 0;
  stack<int> stk;
  int cur = 0;
  while (cur < N)
  {
    if (a[cur] > 0)
    {
      if (cur == N-1) break;

      stk.push(cur);
      cur = min(cur + a[cur], N - 1);
      ++cnt;
    }
    else if (a[cur] == 0)
    {
      if (cur == N-1) break;

      if (!stk.empty())
      {
        cur = stk.top();
        --a[cur];
        --cnt;
        stk.pop();
      }
      else
      {
        return -1;
      }
    }
    else
    {
      throw std::runtime_error("bad");
    }
  }
  return cnt;
}

int main()
{
	string str("");
	getline(cin, str);
	int a[2000];
	int i = 0;
	char *p;
	int count = 0;
	
	const char* strs = str.c_str();
	p = strtok((char *)strs, " ");
	while(p)
	{
		a[i] = atoi(p);
		count++;
		p = strtok(NULL, " ");
		i++;
		if(i >= 2000)
			break;
	}

	int num = solution(a, count);
	cout << num << endl;
	return 0;
}
