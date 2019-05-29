#include <bits/stdc++.h>
using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  int A=1, B=2;
  uniform_int_distribution<> dis(A, B);
  
  int tc;
  cin >> tc;
  while(tc--)
  {
    string str;
    stringstream ss;
    ss << tc;
    ss >> str;
    str = "intro"+str;
    freopen(str.data(),"w",stdout);
    // Code goes here ...
    // dis(gen) produces a number between A and B
    int n = 5;
    cout << n << endl;
    for(int i=1;i<=n;++i)
      cout << dis(gen)<< " \n"[i == n];
    int m = 15;
    uniform_int_distribution<> dis1(1, n);
    cout << m << endl;
    while(m--)
    {
      int l = dis1(gen), r = dis1(gen);
      int d = dis(gen);
      if(l > r) swap(l, r);
      cout << l << ' ' << r << ' ' << d << endl;
    }
    fflush(stdout);
  }

  return 0;
}
