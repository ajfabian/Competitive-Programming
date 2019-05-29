/*
 * // code time: 22
 * Idea: Greedy.
 * 
 * Using the following strategy we will need at most 2(n-1) swaps, which
 * is less than 2n.
 * 
 * To sort the list we pick one lucky number (any-one will do), this one
 * will be the one we will use in order to put every other element in
 * its position, and we'll keep track of the picked element's position.
 * 
 * From left to right let the current position be i, we answer the question
 * what's the element that must be in this position? let the answer be x,
 * now suppous x is in position p all we need to do is to move x from p
 * to i. We can do this in at most two steps: swap(pos[cur], i), swap(pos[cur], p)
 * Example:
 * pos: 1 2 3
 *   a: 5 4 1 -> 4 is the lucky element picked, and we need to put number 1 
 *              in the first position.
 *   a: 4 5 1 -> this is how it's after we move 4 to the position where number 1
 *              must be.
 *   a: 1 5 4 -> and now number 1 is in its place, after moving 4 to where number 1 is.
 * That's it, in at most two steps we can move every element to its position.
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
{a = vector<T>(n);for(T& i: a) scanf("%d", &i);}
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

bool is_lucky(int x)
{
  while(x)
  {
    if(x % 10 != 4 && x % 10 != 7) return false;
    x /= 10;
  }
  return true;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  int n;
  scanf("%d", &n);
  vector<int> a;
  na(a, n);
  vector<int> sorted = a;
  sort(all(sorted));
  
  map<int, set<int>> pos;
  int pluck = -1, is_sorted = true;
  for(int i=0;i<n;++i)
  {
    if(i > 0 && a[i] < a[i-1]) is_sorted = false;
    if(is_lucky(a[i]))
      pluck = a[i];
    pos[a[i]].ins(i);
  }
  
  if(is_sorted) return !(cout << "0\n");
  
  if(pluck == -1) return !(cout << "-1\n");
  
  int lock=-1;
  for(int i=0;i<n;++i)
    if(pluck == sorted[i])
    {
      lock = i;
      break;
    }
  
  int cur = *pos[pluck].begin();
  pos[pluck].ers(cur);
  
  vector<pii> ans;
  for(int i=0;i<n;++i)
  {
    int j=i;
    if(j == lock) continue;
    
    int needed = sorted[j];
    int whereis = *pos[needed].begin();
    pos[needed].ers(whereis);
    
    if(whereis == j) continue; // already on its position
    if(cur != j)
    {
      pos[a[j]].ers(j);
      pos[a[j]].ins(cur);
      ans.eb(cur, j);
      swap(a[j], a[cur]);
      swap(cur, j);
    }
    ans.eb(cur, whereis);
    swap(a[cur], a[whereis]);
    swap(cur, whereis);
  }
  
  printf("%d\n", sz(ans));
  for(pii t: ans)
    printf("%d %d\n", t.fr+1, t.sc+1);
  
  return 0;
}
