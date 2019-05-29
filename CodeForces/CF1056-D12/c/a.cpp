// editorial: https://codeforces.com/blog/entry/63461
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define INIT ios_base::sync_with_stdio(false);\
             cin.tie(0),cout.tie()
//~ #define endl '\n'
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

const int N = 2222;
int must[N];

void choose(int x)
{
  printf("%d\n", x);
  //~ cout << x << "\n";
  fflush(stdout);
}

int get()
{
  int x;
  //~ cin >> x;
  scanf("%d", &x);
  fflush(stdout);
  if(x == -1) exit(0);
  return x;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int n, m;
  //~ cin >> n >> m;
  scanf("%d%d", &n, &m);
  vector<int> p(2*n+1, 0);
  multiset<pii> powers;
  for(int i=1;i<=2*n;++i)
  {
    //~ cin >>p[i];
    scanf("%d", &p[i]);
    powers.ins(mp(p[i], i));
  }
  
  set<pair<int,pii>> s;
  for(int i=1;i<=m;++i)
  {
    int u,v;
    //~ cin >> u >> v;
    scanf("%d%d", &u, &v);
    s.ins(mp(max(p[u], p[v]), mp(min(u, v), max(u, v))));
    must[u] = v;
    must[v] = u;
  }
  
  int turn, last=-1;
  //~ cin >> turn;
  scanf("%d", &turn);
  
  for(int i=1;i<=2*n;++i, turn = turn == 1 ? 2: 1 )
  {
    if(turn == 1) // my turn
    {
      if(~last)
      {
        if(must[last])
        {
          choose(must[last]);
          powers.ers(mp(p[must[last]], must[last]));
          
          auto it = s.find(mp(max(p[must[last]], p[last]),
            mp(  min(must[last], last), max(must[last], last) )));
          s.ers(it);
          
          must[must[last]] = 0;
          must[last] = 0;
        }else
        {
          if(sz(s) > 0)
          {
            auto it = s.end();
            it--;
            int ch;
            if(p[it->sc.fr] > p[it->sc.sc])
              choose(ch = it->sc.fr);
            else choose(ch = it->sc.sc);
            
            powers.ers(mp(it->fr, ch));
            must[must[ch]] = 0;
            must[ch] = 0;
            s.ers(it);
          }else
          {
            auto it = powers.end();
            it--;
            choose(it->sc);
            powers.ers(it);
          }
        }
      }else
      {
        if(sz(s) > 0)
        {
          auto it = s.end();
          it--;
          int ch;
          if(p[it->sc.fr] > p[it->sc.sc])
            choose(ch = it->sc.fr);
          else choose(ch = it->sc.sc);
          
          powers.ers(mp(it->fr, ch));
          must[must[ch]] = 0;
          must[ch] = 0;
          s.ers(it);
        }else
        {
          auto it = powers.end();
          it--;
          choose(it->sc);
          powers.ers(it);
        }
      }
      
    }else
    {
      last = get();
      if(last == -1) return 0;
      powers.ers(mp(p[last], last));
    }
  }
  
  return 0;
}
