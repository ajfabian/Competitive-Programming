#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
typedef pair<int,int> pii;

const int inf = 1e6+7;

#define mp make_pair
#define fr first
#define sc second

int mat[N][N];
int dom[N][N];
int cost[N][N];

const int mr[]{0,0,-1,1},
          mc[]{-1,1,0,0};

int seen[N][N];

int main()
{
  //~ freopen("in", "r", stdin);
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  int n, m, p;
  cin >> n >> m >> p;
  vector<int> s(p+1);

  for(int i=1;i<=p;++i)
    cin >> s[i];

  vector<vector<pii>> start(p+1);
  for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
    {
      char c;
      cin >> c;
      if(c == '.') mat[i][j] = 0;
      else if(c == '#') mat[i][j] = -1;
      else
      {
        int pid = c-'0';
        mat[i][j] = pid;
        start[pid].emplace_back(i, j);
        dom[i][j] = pid;
      }
    }



  int totempty = 0;
  for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
    {
        if(!dom[i][j] && ~mat[i][j]) ++totempty;
        cost[i][j] = inf;
      }
  vector<queue<pii>> Q(p+1);
  for(int i=1;i<=p;++i)
    for(auto f: start[i])
      Q[i].push(f), cost[f.fr][f.sc] = 0,seen[f.fr][f.sc] = 1;

  int mk=0;
  while(totempty > 0)
  {
    bool upd = false;
    ++mk;
    for(int cur=1;cur<=p;++cur)
    {
      queue<pii>& q = Q[cur];
      set<pii> tmp;
      while(!q.empty())
      {
        int r = q.front().fr;
        int c = q.front().sc;
        q.pop();

        for(int k=0;k<4;++k)
        {
          int nr = r + mr[k];
          int nc = c + mc[k];
          if(nr > n || nc >m || nr < 1 || nc < 1 || mat[nr][nc] == -1 || (dom[nr][nc] && dom[nr][nc] != cur )|| (seen[nr][nc] && seen[nr][nc] < mk)) continue;

          if(cost[nr][nc] > cost[r][c] + 1)
          {


            if(cost[r][c] + 1 <= s[cur])
            {
              cost[nr][nc] = cost[r][c] + 1;
              if(!dom[nr][nc]) totempty--;
              dom[nr][nc] = cur;
              q.emplace(nr, nc);
              upd=true;
              seen[nr][nc] = mk;
            }else
              tmp.insert(mp(r, c));
          }
        }
      }

      for(pii t: tmp)
        cost[t.fr][t.sc] = 0,
        Q[cur].emplace(t.fr, t.sc);
    }
    if(!upd)break;
  }

  vector<int> ans(p+1, 0);
  for(int i=1;i<=n;++i)
      for(int j=1;j<=m;++j)
        if(dom[i][j] > 0) ans[dom[i][j]]++;
  for(int i=1;i<=p;++i)
    cout << ans[i] << ' ';
  cout << endl;
  return 0;
}
