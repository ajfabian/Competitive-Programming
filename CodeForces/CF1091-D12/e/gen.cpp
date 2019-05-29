#include <bits/stdc++.h>
using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  int A=2, B=2;
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
    int n = 5e5;
    cout << n << endl;
    for(int i=1;i<=n/2;++i)
      cout << n << ' ';
    for(int i=1;i<=n/2;++i)
      cout << 3*n/5 << ' ';
    cout << endl;
    // dis(gen) produces a number between A and B
    fflush(stdout);
  }

  return 0;
}
