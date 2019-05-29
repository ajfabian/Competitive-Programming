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

const int N = 1e3+7;
const ll inf = 1e18;

template<typename cap_type>
struct Dinic
{
    static const int MAXV = 3e3+7;
    //~ static const cap_type oo = numeric_limits<cap_type>::max();
    using edge = tuple<int,int,cap_type,int>;
    int s, t, V, layer[MAXV], last[MAXV], last_0[MAXV];
    vector<edge> graph;
    // N-number of nodes
    Dinic(int N)
    :V(N)
    {fill(last, last + N + 1, -1);}
    void eadd(int u, int v, cap_type cap)
    {
        graph.emplace_back(u, v, cap, last[u]);
        last[u] = graph.size() - 1;
        graph.emplace_back(v, u, 0, last[v]);
        last[v] = graph.size() - 1;
    }
    bool bfs()
    {
        fill(layer, layer + V + 1, -1);
        layer[t] = 0;
        queue<int> q; q.push(t);
        while(!q.empty())
        {
            int node = q.front(); q.pop();
            for(int e = last[node]; e != -1; e = get<3>(graph[e]))
            {
                edge& din = graph[e^1];
                if(get<2>(din) > 0 && layer[get<0>(din)] == -1)
                {
                    layer[get<0>(din)] = layer[node] + 1;
                    q.push(get<0>(din));
                }
            }
        }
        return layer[s] != -1;
    }
    cap_type dfs(int node, cap_type flow)
    {
        if(node == t)
            return flow;
        for(int e = last_0[node]; e != -1; e = get<3>(graph[e]))
        {
            edge& dout = graph[e];
            edge& din = graph[e^1];
            last_0[node] = e;
            if(get<2>(dout) > 0 && layer[get<1>(dout)] + 1 == layer[get<0>(dout)])
            {
                cap_type f = dfs(get<1>(dout), min(flow, get<2>(dout)));
                if(f > 0)
                {
                    get<2>(dout) -= f;
                    get<2>(din) += f;
                    return f;
                }
            }
        }
        return 0;
    }
    cap_type getmf(int src, int snk)
    {
        s = src, t = snk;
        cap_type totflow = 0, amt;
        while(bfs())
        {
            for(int i=0;i<=V;i++)
                last_0[i] = last[i];
            while((amt = dfs(s, inf)) > 0)
                totflow += amt;
        }
        return totflow;
    }
};

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, m, s = 0, t;
  cin >> n >> m;
  t = n + m + 1;
  
  Dinic<ll> g(n+m+1);
  
  for(int i=1;i<=n;++i)
  {
    ll x; 
    cin >> x;
    g.eadd(i,t,x);
  }
  
  ll C = 0;
  for(int i=1;i<=m;++i)
  {
    int u, v;
    ll c;
    cin >> u >> v >> c;
    C += c;
    g.eadd(s, i+n, c);
    g.eadd(i+n, u, inf);
    g.eadd(i+n, v, inf);
  }
  
  ll mf = g.getmf(s,t);
  
  cout << -(mf - C) << endl;
  
  return 0;
}
