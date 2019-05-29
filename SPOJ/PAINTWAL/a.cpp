#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define INIT ios_base::sync_with_stdio(false);\
             cin.tie(0),cout.tie()
#define endl '\n'
#define fr first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define ers erase
#define sz(c) ((int)(c).size())
#define all(x) (x).begin(),(x).end()
#define unique(x) (x).resize(unique(all(x))-(x).begin())
#define debug(_fmt,...) \
fprintf(stderr,"("#__VA_ARGS__ ") = (" _fmt")\n",__VA_ARGS__)

template<class T>
void na(vector<T>& a, int n)
{a = vector<T>(n);for(T& i: a) cin >> i;}
template<class T>
void printVector(vector<T>& a)
{for(T& i: a) cout << i << ' '; cout << endl;}
template<class T>
vector<T> shrink(vector<T>& x)
{
  vector<T> vals = x;
  sort(all(vals)); unique(vals);
  for(T& i: x) i = ub(all(vals), i) - vals.begin();
  return vals;
}

typedef unsigned long long ull;

char str[2][10];

vector<pii> pos[27];

void clean()
{
  for(int i=0;i<27;++i)
    pos[i].clear();
}

typedef vector<string> stat;

#define BASE 31
const ull mod = 1e9+7;
ull val(char c)
{
  return max(0ull, (ull)(c - 'A' + 1));
} 
ull ghash(vector<string>& w)
{
  ull res = 0;
  for(auto& s: w)
    for(char c: s)
      res = res * BASE + val(c);
  return res;
}

stat paint(stat& cur, pii from, pii to, char what)
{
  int left = min(from.sc, to.sc);
  int right = max(from.sc, to.sc);
  int bott = max(from.fr, to.fr);
  int top = min(from.fr, to.fr);
  
  //~ cerr << top << ' ' << bott << ' ' << left << ' ' << right << endl;
  
  stat res = cur;
  for(int i=top;i<=bott;++i)
    for(int j=left;j<=right;++j)
      res[i][j] = what;
  return res;
}

void printS(stat& s)
{
  //~ cerr << "State:\n";
  for(auto& i: s)
    cerr << i << endl;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int tt, tc=0;
  scanf("%d", &tt);
  while(tt--)
  {
    int n;
    scanf("%d", &n);
    scanf("%s%s", str[0], str[1]);
    
    for(int i=0;i<2;++i)
      for(int j=0;j<n;++j)
      {
        pos[str[i][j] - 'A'].eb(i, j);
      }
    
    vector<string> wall;
    wall.eb(str[0]);
    wall.eb(str[1]);
    
    ull ed = ghash(wall);
    //~ cerr << "Target: " << ed << endl;
    map<ull, bool> mk;
    vector<string> st(2, "");
    for(int i=0;i<2;++i)
      for(int j=0;j<n;++j)
        st[i] += (char)(0);
    
    queue<pair<int, stat>> q;
    q.emplace(0, st);
    mk[ghash(st)] = 1;
    int totalSteps = 0;
    while(!q.empty())
    {
      auto cur = q.front();
      q.pop();
      ++totalSteps;
      //~ cerr << "CURRENT\n";
      //~ printS(cur.sc);
      if(ghash(cur.sc) == ed)
      {
        printf("Case #%d: %d\n", ++tc, cur.fr);
        break;
      }
      
      for(int i=0;i<27;++i)
      {
        if(pos[i].empty())continue;
        for(auto it = pos[i].begin(); it != pos[i].end(); it++)
          for(auto jt = it; jt != pos[i].end(); jt++)
          {
            //~ cerr << "NXT STATE: " << (char)(i + 'A') << " " << it->fr << ' ' << it->sc << ' ' << jt->fr << ' ' << jt->sc << endl;
            auto nxtStat = paint(cur.sc, *it, *jt, (char)(i + 'A'));
            //~ printS(nxtStat);
            if(mk.count(ghash(nxtStat))) continue;
            mk[ghash(nxtStat)] = 1;
            q.emplace(cur.fr + 1, nxtStat);
          }
      }
    }
    //~ cerr << totalSteps << endl;
    clean();
  }
  
  return 0;
}
