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

const int N = 1e5+7;

int f[N], nextL[N], nextR[N];

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  int n;
  cin >> n;
  string s;
  cin >> s;
  
  int last=-1, first=1e5+7;
  int lpos=-1;
  for(int i=0;i<n;++i)
  {
    if(s[i] == 'G')
    {
      last = i;
      first = min(first, i);
      if(~lpos) nextL[i] = lpos;
      else lpos = nextL[i] = i;
    }else
    {
      lpos = -1;
    }
  }
  
  lpos = -1;
  for(int i=n-1;~i;--i)
  {
    if(s[i] == 'G')
    {
      if(~lpos) nextR[i] = lpos;
      else lpos = nextR[i] = i;
    }else
    {
      lpos = -1;
    }
  }
  //~ return 0;
  //~ cerr << "LEFT: ";
  //~ for(int i=0;i<n;++i)
    //~ cerr << nextL[i] << ' ';
  //~ cerr << endl;
  //~ cerr << "RIGHT: ";
  //~ for(int i=0;i<n;++i)
    //~ cerr << nextR[i] << ' ';
  //~ cerr << endl;
  
  int ans=0;
  for(int i=0;i<n;++i)
  {
    if(s[i] == 'G')
    {
      ans = max(ans, nextR[i] - nextL[i] + 1);
    }else
    {
      bool a = (i > 0 && s[i-1] == 'G');
      bool b = (i+1 < n && s[i + 1] == 'G');
      if(a && b)
      {
        if(last > nextR[i+1]) ans = max(ans, nextR[i+1] - nextL[i-1] + 1);
        else ans = max(ans, nextR[i+1] - nextL[i-1]);
        if(first < nextL[i-1]) ans = max(ans, nextR[i+1] - nextL[i-1] + 1);
        else ans = max(ans, nextR[i+1] - nextL[i-1]);
      }else if(a)
      {
        if(last > i) ans = max(ans, i - nextL[i-1] + 1);
      }else if(b)
      {
        if(first < i) ans = max(ans, nextR[i+1] - i + 1);
      }
    }
  }
  cout << ans << endl;
   
  return 0;
}
