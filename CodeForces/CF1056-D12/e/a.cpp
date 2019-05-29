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
#define BASE 29
const ull Mod=1e9+7;
ull powe[1000007];
void init()
{
  powe[0]=1;
  for(int i=1;i<=1000006;i++)powe[i]=(powe[i-1]*BASE)%Mod;
}
int val(char x){return x-'a'+1;}
struct HashedString
{  
  string str;
  vector<ull> hash;
  HashedString(){}
  HashedString(string &str)
    :str(str), hash(str.size())
  {
    hash[0] = val(str[0]);
    for(int i=1;i<(int)hash.size();++i)
      hash[i] = (hash[i-1]*BASE%Mod + val(str[i]))%Mod;
  }
  ull hashCode(){return hash.back();}
  ull get_hash(int i,int j)
  {
    if(i > 0) return (hash[j]+Mod - hash[i-1]*powe[j-i+1]%Mod)%Mod;
    return hash[j];
  }
};


int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  init();
  
  string s, t;
  cin >> s >> t;
  int t0=0, t1=0, k0=1e6+7, k1=1e6+7;
  for(int i=0;i<sz(s); ++i)
    if(s[i] =='0') ++t0, k0 = min(k0, i);
    else ++t1, k1 = min(k1, i);
    
  HashedString hs(t);
  
  int ans = 0;
  for(int r0s = 1;r0s <= sz(t);++r0s)
  {
    int r1s = sz(t) - t0 * r0s;
    if(r1s <= 0) break;
    if(r1s % t1) continue;
    r1s /= t1;
    
    ull h0 = hs.get_hash(k0 * r1s, k0 * r1s + r0s-1);
    ull h1 = hs.get_hash(k1 * r0s, k1 * r0s + r1s-1);
    
    if(h0 == h1) continue;
    bool ok=true;
    //~ cout << "checking with r0 size: " << r0s << endl; 
    //~ cout << "r0 = t[" << k0 * r1s << " " << k0 * r1s + r0s - 1 << "]  with hash " << h0 << endl; 
    //~ cout << "r1 = t[" << k1 * r0s << " " << k1 * r0s + r1s - 1 << "]  with hash " << h1 << endl; 
    for(int i=0, j=0;i<sz(s) && ok;++i)
    {
      //~ cerr << j << endl;
      if(s[i] == '0')
      {
        ull tmp;
        //~ cerr << "asking " << j << ' ' << j + r0s - 1;
        if((tmp = hs.get_hash(j, j + r0s - 1)) != h0) ok=false;
        else j += r0s;
        //~ cerr << " with hash " << tmp << endl;
      }
      if(s[i] == '1')
      {
        ull tmp;
        //~ cerr << "asking " << j << ' ' << j + r1s - 1;
        if((tmp = hs.get_hash(j, j + r1s - 1)) != h1) ok=false;
        else j += r1s;
        //~ cerr << " with hash " << tmp << endl;
      }
    }
    //~ cerr << "result " << ok << endl; 
    //~ cerr << endl;
    if(ok) ++ans;
  }
  cout << ans << endl;
  
  return 0;
}
