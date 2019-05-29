#pragma GCC optimize("Ofast")

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

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

const int N = 2e5+7;


  int n, m;
int whereinA[N], a[N];
int whereinB[N], b[N];

int arr[N];

ordered_set ft[N];

void build()
{
  for(int i=1;i<=n;++i)
    for(int j=i;j<N;j+=j&-j)
      ft[j].ins(arr[i]);
}

void updera(int pos,int out)
{
  for(;pos<N;pos+=pos&-pos)
    ft[pos].ers(out);
}

void updins(int pos,int inn)
{
  for(;pos<N;pos+=pos&-pos)
    ft[pos].ins(inn);
}

int qry(int la, int ra, int lb, int rb)
{
  int res = 0;
  for(;ra;ra-=ra&-ra)
    res += ft[ra].order_of_key(rb+1) - ft[ra].order_of_key(lb);
  --la;
  for(;la;la-=la&-la)
    res -= ft[la].order_of_key(rb+1) - ft[la].order_of_key(lb);
  return res;
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  scanf("%d%d", &n, &m);
  
  for(int i=1;i<=n;++i)
    scanf("%d", &a[i]);
  for(int i=1;i<=n;++i)
    scanf("%d", &b[i]);
  
  for(int i=1;i<=n;++i)
    whereinA[a[i]] = i,
    whereinB[b[i]] = i;
  
  for(int i=1;i<=n;++i)
    arr[i] = whereinB[a[i]];
  
  build();
  
  while(m--)
  {
    int tt;
    scanf("%d", &tt);
    if(tt == 1)
    {
      int la, ra, lb, rb;
      scanf("%d %d %d %d", &la, &ra, &lb, &rb);
      printf("%d\n", qry(la, ra, lb, rb));
    }else
    {
      int x, y;
      scanf("%d%d", &x, &y);
      //~ continue;
      //~ cerr << "in " << whereinA[b[x]] << " = " << y << " out " << x << endl;
      //~ cerr << "in " << whereinA[b[y]] << " = " << x << " out " << y << endl;
      updera(whereinA[b[x]], x);
      updera(whereinA[b[y]], y);
      updins(whereinA[b[x]], y);
      updins(whereinA[b[y]], x);
      //~ for(int i=1;i<=13;++i)
      //~ {
        //~ cerr << i << " ";
        //~ for(int j: t[i])
          //~ cerr << " " << j;
        //~ cerr << endl;
      //~ }
      //~ break;
      whereinB[b[x]] = y;
      whereinB[b[y]] = x;
      swap(b[x], b[y]);
    }
  }
  
  
  return 0;
}
