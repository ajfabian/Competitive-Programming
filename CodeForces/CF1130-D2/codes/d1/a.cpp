#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

int fur(int cur, int i, int j)
{
  if(j == -1) return i;
  vector<int> el{cur, i, j};
  sort(el.begin(), el.end());
  queue<int> q;
  for(int e: el) q.emplace(e);
  while(q.front() != cur)
  {
    q.push(q.front());
    q.pop();
  }
  while(q.size() > 1)
    q.pop();
  return q.front();
}

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> station(n+1);
  vector<int> closest(n+1, -1);
  for(int i=1;i<=m;++i)
  {
    int a,b;
    scanf("%d%d", &a, &b);
    station[a].push_back(b);
    if(closest[a]==-1) closest[a] = b;
    else
    {
      if(b < a)
      {
        if(closest[a] < a) closest[a] = min(closest[a], b);
      }else
      {
        if(closest[a] > a) closest[a] = min(closest[a], b);
        else closest[a] = b;
      }
    }
  }
  for(int i=1;i<=n;++i)
  {
    sort(station[i].begin(), station[i].end());
    for(int j=0;j<(int)station[i].size();++j)
    {
      if(closest[i] == station[i][j])
      {
        swap(station[i][0], station[i][j]);
        break;
      }
    }
    //~ cerr << i << ' ' << closest[i] << endl;
  }
  
  for(int i=1;i<=n;++i)
  {
    //~ cerr << "\n>> station: " << i << endl;
    int j = i, bg = -1, left=m, tt = 0;
    auto S = station;
    while(left || (~bg && j != bg))
    {
      if(bg == j) bg = -1;
      //~ cerr << j;
      // candies left??
      if(S[j].size())
      {
        --left;
        bg = fur(j, S[j].back(), bg);
        //~ cerr << " loaded w destiny: " << S[j].back();
        S[j].pop_back();
      }
      //~ cerr << endl;
      
      // advance
      ++tt;
      ++j;
      if(j > n) j =1;
    }
    printf("%d ", tt);
  }
  printf("\n");
  
  return 0;
}
