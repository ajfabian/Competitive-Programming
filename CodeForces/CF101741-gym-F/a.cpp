/* Idea: Use randomization.
 * 
 * It can be seen that maximum number of erasings being k implies
 * that the number of elements in the solution set (the subset of a with
 * maximum gcd) is at least n - k.
 * So the probability P that an element belongs to the solution set is
 *  P >= (n - k) / n
 * this value reaches its minimum with k = n / 2 (subject to problem constrains)
 * from here comes out that (n - k) / n = (n - n / 2) / n = 1/2
 * which give us the result of P >= 1/2.
 * So the probability that an element doesn't belong to the answer is 1/2.
 * 
 * Now for the algorithm let's iterate over the first elements of the array
 * keeping a current gcd and escaping elements which lead us to a lesser
 * gcd that the current global answer. If at some point the number of
 * escaped elements is greater than k then we couldn't form a valid (better)
 * subsequence (we possibly need to erase more than k elements to improve
 * the best gcd).
 * Obviously this solution as it is doesn't work, but if we make it not
 * deterministic (randomly shuffle the array) it will have a great
 * probability of finding the correct solution ((1/2 ** n-k) ** #oftries).
 * 
 * Note: There are other approaches to this problem but all of them use
 * randomization.
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
{a = vector<T>(n);for(T& i: a) scanf("%lld", &i);}
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

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  random_device rd;
  mt19937 gen(rd());
  
  int n, k;
  scanf("%d%d", &n, &k);
  vector<ll> a; na(a, n);
  
  ll ans = 0;
  while(clock() <= 3.3 * CLOCKS_PER_SEC)
  {
    shuffle(all(a), rd);
    ll gcd = 0;
    int t = k;
    for(int i=0; i < n;++i)
    {
      ll ng = __gcd(gcd, a[i]);
      if(ng <= ans) --t;
      else gcd = ng;
      if(t < 0)break;
    }
    if(t >= 0) ans = max(ans, gcd);
  }
  
  cout << ans << endl;
  
  return 0;
}
