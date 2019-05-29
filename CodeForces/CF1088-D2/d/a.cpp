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

int a=0,b=0,x=0,y=0;

pii askBit(int i)
{
  int c = a | (1 << i);
  int d = b | (1 << i);
  int ans1, ans2;
  cout << "? " << a << ' ' << d  << endl;
  cin >> ans1;
  cout << "? " << c << ' ' << b  << endl;
  cin >> ans2;
  
  if(ans1 == -1 && ans2 == 1) return mp(0,0);
  if(ans1 == 1 && ans2 == -1) return mp(1,1);
  
  pii res;
  if(x < y) res = mp(0, 1);
  else res = mp(1, 0);
  
  if(ans1 == 0) x = y = 0;
  if(ans1 == -1) x = 0, y = 1;
  if(ans1 == 1) x = 1, y = 0;
  
  return res;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  cout << "? 0 0" << endl;
  int tmp;
  cin >> tmp;
  if(tmp > 0) x = 1, y = 0;
  if(tmp < 0) x = 0, y = 1;
  
  for(int i=29;~i;--i)
  {
    pii t = askBit(i);
    a |= t.fr * (1 << i);
    b |= t.sc * (1 << i);
  }
  
  cout << "! " << a << ' ' << b << endl;
  
  return 0;
}
