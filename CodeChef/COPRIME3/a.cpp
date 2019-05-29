/*
 * Idea: Mobius function.
 * 
 * Note: [property] = 1 iff property is true, 0 otherwise.
 * 
 * The problem can be re-written as to find:
 *  sum(i = 1, n, sum (j = i + 1, n, sum(k = j + 1, n, [gcd(ai, aj, ak) == 1])))
 * 
 * As it's known sum(divisors d of n, moibius(d)) = 1 iff n = 1, otherwise is 0.
 * and we can use this to rewrite our inner part of the summation as this:
 * 
 * [gcd(ai, aj, ak) == 1] = sum(divisors d of gcd(ai, aj, ak), mobius(d))
 * 
 * we obtain the following:
 *  sum(i = 1, n, sum (j = i + 1, n, sum(k = j + 1, n, sum(divisors d of gcd(ai, aj, ak), mobius(d)))))
 * 
 * Q: How many times will appear 'mobius(d)' in the sum?
 * A: well if a number divides at the same time ai, aj and ak, then it divides
 *  their gcd. So 'd' will appear always that there are three numbers in the
 * array such that theri gcd is divisible by d. So if there are 'cnt[d]'
 * multiples of 'd' then 'd' will appear in the sum exactly 'Comb(cnt[d], 3)' (number of ways of taking 3 elements out of 'cnt[d]')
 * and so it will do mobius(d).
 * 
 * Now we re-write our formula:
 *  sum(d, 1, N, mobius(d) * Comb(cnt[d], 3))
 * 
 * useful link: https://codeforces.com/blog/entry/53925
 * 
 * */

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

const int N = 1e6+7;

int mob[N], lpf[N];
vector<int> primes;
void sieve()
{
  mob[1] = 1;
  for(int i=2;i<N;++i)
  {
    if(!lpf[i])
    {
      lpf[i] = i;
      mob[i] = -1;
      primes.pb(i);
    }
    
    for(int p: primes)
    {
      if(1ll * i * p >= N) break;
      lpf[i * p] = p;
      if(i % p == 0)
      {
        mob[i * p] = 0;
        break;
      }else mob[i*p] = -mob[i];
    }
  }
}

int cnt[N];
int ff[N];

ll cn3(ll n)
{
  return n * (n - 1) * (n - 2) / 6ll;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  sieve();
  
  int n;cin >> n;
  vector<int> a;
  na(a, n);
  
  for(int i: a)
    ++ff[i];
  
  for(int i = 1; i < N; ++i)
    for(int j = i; j < N; j += i)
      cnt[i] += ff[j];
  
  ll ans = 0;
  for(int i=1;i<N;++i)
    ans += 1ll * mob[i] * cn3(cnt[i]);
  cout << ans << endl;
  
  return 0;
}
