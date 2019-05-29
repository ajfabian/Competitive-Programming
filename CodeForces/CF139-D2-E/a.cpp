/*
 * Idea: use sweep line.
 * 
 * The answer to the problem is the sum over each mushroom of its
 * probability of living multiplied by its score.
 * We can translate the problem to segments that exists with certain probability,
 * then for any point the probability of living is the product of
 * the probabilities of all segments that contains it.
 * Note: Instead of multiply we actually sum the log2 of the numbers and
 * then calculate a power of 2 in order to find the required value.
 * 
 * */

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;

struct Event
{
  int t; // 0 - divide, 1 - mul, 2 - sum, 3 - mushroom
  int x; // coordinate
  ld val; // val
  int pp;
  Event(){}
  Event(int t, int x, ld val, int pp=0)
    : t(t), x (x), val (val), pp(pp){}
  bool operator<(const Event& e)const
  {
    if(x != e.x) return x < e.x;
    return t < e.t;
  }
};

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  vector<Event> E;
  for(int i=1;i<=n;++i)
  {
    int a, h, l, r;
    scanf("%d%d%d%d", &a, &h, &l, &r);
    if(l != 100)
    {
      E.emplace_back(0, a, log2((100 - l) / (ld) 100));
      E.emplace_back(1, a-h, log2((100 - l) / (ld) 100));
    }else
    {
      E.emplace_back(2, a-h, 0, 1);
      E.emplace_back(2, a, 0, -1);
    }
    if(r != 100)
    {
      E.emplace_back(0, a+h+1, log2((100 - r) / (ld) 100));
      E.emplace_back(1, a+1, log2((100 - r) / (ld) 100));
    }else
    {
      E.emplace_back(2, a+1, 0, 1);
      E.emplace_back(2, a+h+1, 0, -1);
    }
  }
  for(int i=1;i<=m;++i)
  {
    int b, z;
    scanf("%d%d", &b, &z);
    E.emplace_back(3, b, z);
  }
  
  sort(E.begin(), E.end());
  ld cur = 0.0, ans = 0.0;
  int sum = 0;
  for(auto e: E)
  {
    if(e.t == 0)
    {
      cur -= e.val;
    }else if(e.t == 1)
    {
      cur += e.val;
    }else if(e.t == 2)
    {
      sum += e.pp;
    }else
    {
      //~ cerr << "mushroom at " << e.x << " value = " << e.val << ' ' << sum << ' ' << cur << endl;
      if(sum == 0)
        ans += pow(2.0, log2(e.val) + cur);
    }
  }
  
  cout << fixed << setprecision(12) << ans << endl;
  
  return 0;
}
