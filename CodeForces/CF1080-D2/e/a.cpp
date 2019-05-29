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
{for(T i: a) cout << i << ' '; cout << endl;}
template<class T>
vector<T> shrink(vector<T>& x)
{
  vector<T> vals = x;
  sort(all(vals)); unique(vals);
  for(T& i: x) i = ub(all(vals), i) - vals.begin();
  return vals;
}

typedef unsigned long long ull;
typedef unsigned int ui;
#define BASE1 29
#define BASE2 31

vector<int> manacher(const vector<pair<ui, ui>> &s)
{
  int n = 2 * s.size(); 
  vector<int> rad(n);
  for(int i=0, j=0, k; i<n; i+=k, j=max(j-k, 0))
  {
    for(; i>=j && i+j+1<n && s[(i-j)/2] == s[(i + j + 1) / 2]; ++j);
    rad[i] = j;
    for(k=1; i>=k && rad[i] >= k && rad[i-k] != rad[i]-k; ++k)
      rad[i+k] = min(rad[i-k], rad[i]-k);
  }
  return rad;
}
bool is_pal(const vector<int> &rad, int b, int e)
{
  int n=rad.size()/2;
  return b >= 0 && e < n && rad[b + e] >= e - b + 1;
}

ll solve(vector<pair<ui, ui>>& h, vector<char>& p)
{
  ll res = 0;
  auto rad = manacher(h);
  vector<int> left(sz(p)), right(sz(p));
  
  int n = sz(p), last = -1;
  for(int i=0;i<n;++i)
  {
    if(!p[i])
    {
      last = -1;
      continue;
    }
    
    if(last == -1)
    {
      last = i;
      left[i] = i;
    }else
    {
      left[i] = last;
    }
  }
  
  last=-1;
  for(int i=n-1;~i;--i)
  {
    if(!p[i])
    {
      last = -1;
      continue;
    }
    
    if(last == -1)
    {
      last = i;
      right[i] = i;
    }else
    {
      right[i] = last;
    }
  }
  
  //~ cout << "rad: ";printVector(rad);
  for(int i=0,j=0;i<n;++i, j+=2)
  {
    if(!p[i]) continue;
    if(rad[j]) // impar
    {
      int le = max(left[i], i - rad[j] / 2);
      int ri = min(right[i], i + rad[j] / 2);
      res += min(abs(i - le + 1), abs(ri - i + 1));
    }
    if(rad[j+1]) // par
    {
      int le = max(left[i], i - rad[j+1] / 2 + 1);
      int ri = min(right[i], i + rad[j+1] / 2);
      res += min(abs(i - le + 1), abs(ri - i));
    }
  }
  
  return res;
}

const int N = 256;

int ff[N];
char P[N][N][N];
pair<ui, ui> H[N][N][N];


int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, m;
  cin >> n >> m;
  vector<vector<char>> a(n, vector<char>(m));
  for(auto& r: a)
    for(auto& i: r) cin >> i;
  
  for(int i=0;i<n;++i)
  {
    for(int l=0;l<m;++l)
    {
      memset(ff, 0, sizeof ff);
      int nods = 0;
      for(int r = l;r < m;++r)
      {
        ff[(int)a[i][r]] ^= 1;
        if(ff[(int)a[i][r]]) ++ nods;
        else --nods;
        if(nods <= 1)
          P[i][l][r] = 1;
        else P[i][l][r] = 0;
      }
    }
  }
  
  vector<ui> pot1(27);
  vector<ui>pot2(27);
  pot1[0] = 1;
  pot2[0] = 1;
  for(int i=1;i<27;++i)
    pot1[i] = pot1[i-1] * BASE1,
    pot2[i] = pot2[i-1] * BASE2;
  
  for(int i=0;i<n;++i)
  {
    for(int l=0;l<m;++l)
    {
      ui h1 = 0;
      ui h2 = 0;
      for(int r = l;r < m;++r)
      {
        h1+=pot1[(int)(a[i][r] - 'a')];
        h2+=pot2[(int)(a[i][r] - 'a')];
        H[i][l][r] = mp(h1, h2);
      }
    }
  }
  
  ll ans = 0;
  for(int i = 0;i<m;++i)
  {
    for(int j=i;j<m;++j)
    {
      //~ cout << "Considerando: " << i << ' ' << j << endl;
      vector<pair<ui, ui>> h;
      vector<char> p;
      for(int k=0;k<n;++k)
      {
        h.pb(H[k][i][j]);
        p.pb(P[k][i][j]);
      }
      //~ cout << "h: ";printVector(h);
      //~ cout << "p: ";printVector(p);
      ll tmp = solve(h, p);
      //~ cout << "found: " << tmp << endl;
      ans += tmp;
    }
  }
  cout << ans << endl;
  
  return 0;
}
