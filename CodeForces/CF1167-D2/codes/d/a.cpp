#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+7;

char s[N];

int main()
{
  int n;
  scanf("%d", &n);
  
  scanf("%s", s);
  
  vector<int> stk(2, 0);
  for(int i=0;i<n;++i)
  {
    if(s[i] == '(')
    {
      if(stk[0] <= stk[1])
      {
        ++stk[0];
        printf("0");
      }else
      {
        ++stk[1];
        printf("1");
      }
    }else
    {
      if(stk[0] >= stk[1])
      {
        --stk[0];
        printf("0");
      }else
      {
        --stk[1];
        printf("1");
      }
    }
  }
  printf("\n");
  
  return 0;
}
