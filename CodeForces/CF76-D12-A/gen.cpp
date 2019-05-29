#include <bits/stdc++.h>
using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  
  
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
    int n = 3, m = 4;
    int A=1, B=n;
    uniform_int_distribution<> dis(A, B);
    cout << n << ' ' << m << endl;
    cout << dis(gen) << ' ' << dis(gen) << endl;
    for(int i=1;i<=m;++i)
    {
      cout << dis(gen) << ' ' << dis(gen) << ' ' << dis(gen) << ' ' << dis(gen) << endl;
    }
    fflush(stdout);
  }

  return 0;
}
