#include <bits/stdc++.h>
using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  int A=1, B=1000;
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
    fflush(stdout);
  }

  return 0;
}
