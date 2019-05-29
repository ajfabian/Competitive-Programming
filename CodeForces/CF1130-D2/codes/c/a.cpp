#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

struct cell
{
  int x, y;
  cell(int x=0, int y=0)
    : x(x), y(y){}
  ll operator%(cell c)
  {
    return (x - c.x)*(x - c.x) + (y - c.y)*(y - c.y);
  }
  
};

const int N = 55;

const int mr[]{-1,1,0,0},
          mc[]{0,0,-1,1};

int n;
bool mk[N][N];
char mm[N][N];

void getCells(cell st, vector<cell>& ve)
{
  memset(mk, 0, sizeof mk);
  queue<cell> q;
  q.emplace(st);
  ve.push_back(st);
  mk[st.x][st.y] = 1;
  while(!q.empty())
  {
    int x = q.front().x, y = q.front().y;
    q.pop();
    for(int k=0;k<4;++k)
    {
      int nx = x + mr[k];
      int ny = y + mc[k];
      if(nx > n || nx < 1 || ny > n || ny < 1) continue;
      if(mk[nx][ny] || mm[nx][ny] != '0') continue;
      ve.emplace_back(nx, ny);
      mk[nx][ny] = 1;
      q.emplace(nx, ny);
    }
  }
}

int main()
{
  scanf("%d", &n);
  cell st, ed;
  scanf("%d%d%d%d", &st.x, &st.y, &ed.x, &ed.y);
  for(int i=1;i<=n;++i)
    for(int j=1;j<=n;++j)
      cin >> mm[i][j];
  
  vector<cell> bobCells, aliceCells;
  
  getCells(st, bobCells);
  getCells(ed, aliceCells);
  
  ll ans = 1e18;
  for(cell& c1: bobCells)
    for(cell& c2: aliceCells)
      ans = min(ans , c1 % c2);
  cout << ans << endl;
  
  return 0;
}
