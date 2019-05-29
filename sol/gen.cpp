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
  
  return 0;
}
