#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b)
{
  return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[])
{
  srand(argc > 1 ? atoi(argv[1]) : time(nullptr));
  // test case generator here
  const int M = 10;
  int n = rand(1, 1);
  int m = 1;
  cout << n << ' ' << m << endl;
  for(int i=1;i<=n;++i)
  {
    int l;
    cout << rand(0, M) << ' ' << rand(0, M) << ' ' << (l = rand(0, 100));
    cout << ' ' << rand(0, 100 - l) << '\n';
  }
  for(int i=1;i<=m;++i)
    cout << rand(0, 0) << ' ' << rand(1, 5) << endl;
  return 0;
}
