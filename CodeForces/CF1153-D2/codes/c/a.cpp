#include <bits/stdc++.h>
using namespace std;

const int N = 3e5+7;

char s[N];
int n;

bool can()
{
  if(n == 2) return true;
  if(s[1] == ')' || s[n-2] == '(') return false;
  s[1] = '(';
  s[n-2] = ')';
  int o = 0, c = 0, lim = (n-2)/2;
  for(int i=1;i<n-1;++i)
    if(s[i] == '(') ++o;
    else if(s[i] == ')') ++c;
  
  if(o > lim || c > lim) return false;
  
  int sum = 0;
  for(int i=1;i<n-1;++i)
  {
    if(s[i] == '(') sum ++;
    else if(s[i] == '?')
    {
      if(o < lim) s[i] = '(', o++, sum++;
      else  s[i] = ')', c++, sum--;
    }else // then ')'
      sum--;
    if(sum < 0) return false;
  }
  
  return sum == 0;
}

int main()
{
  scanf("%d%s", &n, s);
  if(n&1)
  {
    printf(":(\n");
    return 0;
  }
  
  if(s[0] == ')' || s[n-1] == '(')
  {
    printf(":(\n");
    return 0;
  }
  
  s[0] = '(', s[n-1] = ')';
  
  if(!can())
  {
    printf(":(\n");
    return 0;
  }
  
  printf("%s\n", s);
  
  
  return 0;
}
