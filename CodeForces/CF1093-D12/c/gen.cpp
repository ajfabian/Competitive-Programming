#include <bits/stdc++.h>
using namespace std;

int main()
{
  random_device rd;
  mt19937 gen(rd());
  int A=1, B=4;
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
    int n = 6;
    cout << n<<endl;
    vector<int> t;
    for(int i=1;i<=n;++i)
      t.push_back(dis(gen));
    sort(t.begin(), t.end());
    
    for(int i=0;i<n/2;++i)
      cout << t[i] + t[n-i-1] << ' ';
    cout << endl;
    fflush(stdout);
  }

  return 0;
}
