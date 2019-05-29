#include <bits/stdc++.h>
using namespace std;

int main()
{
  char car;
  int a=46543213,b=545687132;
  //~ cin >> a >> b;
  while(1)
  {
    int c, d;
    cin >> car >> c >> d;
    cerr << "received: "<< car << ' ' << c << ' ' << d;
    if(car == '!') return cerr << endl, 0;
    
    if((a ^ c) < (b ^ d)) cout <<  -1 << endl, cerr << " <\n";
    if((a ^ c) > (b ^ d)) cout <<  1 << endl, cerr << " >\n";
    if((a ^ c) == (b ^ d)) cout <<  0 << endl, cerr << " =\n";
  }
  return 0;
}
