#include <bits/stdc++.h>
using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  int A=4, B=7;
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
    int n = dis(gen), q = 10;
    cout << n << ' ' << q << endl;
    while(q--)
    {
      if(n > 1)
      {
        int t = rand()%2 + 1;
        cout << t << ' ';
        if(t == 1)
        {
          uniform_int_distribution<> dis1(1, n-1);
          int p = dis1(gen);
          cout << p << endl;
          n-=p;
        }else
        {
          uniform_int_distribution<> dis1(0, n);
          int i =dis1(gen), j = dis1(gen);
          if(i > j) swap(i, j);
          if(i == j)
          {
            if(i) -- i;
            else ++j;
          }
          cout << i << ' ' << j << endl;
        }
      }else
      {
        cout << "2 0 1\n";
      }
    }
    // dis(gen) produces a number between A and B
    fflush(stdout);
  }

  return 0;
}
