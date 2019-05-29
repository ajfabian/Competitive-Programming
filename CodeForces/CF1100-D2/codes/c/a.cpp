#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  cerr << pi << endl;
  int n;
  double r;
  cin >> n >> r;
  
  double alph = 2.0 * pi / n;
  
  double l = r * sqrt(2.0 * (1.0 - cos(alph)));
  
  cout << fixed << setprecision(12) << l * r / (2 * r - l) << endl;
  
  
  
    
  return 0;
}
