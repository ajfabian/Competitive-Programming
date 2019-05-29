#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

const int inf = 1e9;

struct Trie2
{
  Trie2(){}
  struct node
  {
    node(){}
    int mini=inf;
    int nxt[10]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  }nullnode;
  vector<node> t{nullnode};

  inline void convert(int val, short p[6])
  {
    int cnt=0;
    while(val > 0)
    {
      p[cnt++] = val % 10;
      val /= 10;
    }
    while(cnt < 6) p[cnt++] = 0;
    reverse(p, p + 6);
  }

  void add(int key, int val)
  {
    short p[6];
    convert(key, p);

    int s = 0;
    for(int i=0;i<6;++i)
    {
      if(t[s].nxt[p[i]] == -1)
      {
        t[s].nxt[p[i]] = sz(t);
        t.pb(nullnode);
      }
      s = t[s].nxt[p[i]];
      t[s].mini = min(t[s].mini, val);
    }
  }

  int qry(int st, int ed)
  {
    //~ assert(st <= ed);
    short S[6], E[6];
    convert(st, S);
    convert(ed, E);

    int s=0, i, sta = 0, ret = inf, s1=-2, s2=-2;
    for(i = 0;i < 6;++i)
    {
      if(S[i] != E[i]) ++ sta;
      if(sta == 0)
      {
        if(t[s].nxt[S[i]] == -1) return inf;
        s = t[s].nxt[S[i]];
      }else
      {
        for(int j=S[i]+1; j<E[i];++j)
          if(~t[s].nxt[j])
            ret = min(ret, t[t[s].nxt[j]].mini);
        s1 = t[s].nxt[S[i]];
        s2 = t[s].nxt[E[i]];
        break;
      }
    }

    if(i == 6) return assert(sta == 0), t[s].mini;

    assert(s1 != -2 && s2 != -2);
    
    int j;
    for(j=i+1;s1 != -1 && j<6;++j)
    {
      for(int k=S[j]+1;k<10;++k) if(~t[s1].nxt[k])
        ret = min(ret, t[t[s1].nxt[k]].mini);
      s1 = t[s1].nxt[S[j]];
    }
    
    if(~s1) assert(j == 6), ret = min(ret, t[s1].mini);
    
    for(j=i+1;s2 != -1 && j<6;++j)
    {
      for(int k=E[j]-1;~k;--k) if(~t[s2].nxt[k])
        ret = min(ret, t[t[s2].nxt[k]].mini);
      s2 = t[s2].nxt[E[j]];
    }
    
    if(~s2) assert(j == 6), ret = min(ret, t[s2].mini);

    return ret;
  }
};

int main()
{
  Trie2 t2;
  while(1)
  {
    int t, x, y;
    cin >> t >> x >> y;
    if(t == 1) t2.add(x, y);
    else cout << t2.qry(x, y) << endl;
  }
  return 0;
}
