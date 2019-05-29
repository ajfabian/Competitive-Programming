#include <bits/stdc++.h>
using namespace std;

int a[1111];

int main()
{
	int n, m;
	cin >> n >> m;
	
	//~ if(m == 0) return !(cout << "1\n");
	//~ if(m == n) return !(cout << "0\n");
	
	for(int i=0;i<n && m > 0;i+=2)
		a[i] = 1, --m;
	
	for(int i=1;i<n && m > 0;i+=2)
		a[i] = 1, --m;
	
	int ans = 0;
	for(int i=0;i<n;++i)
		if(!a[i] && (i == 0 || a[i-1])) ++ans;
	cout << ans << endl;
	return 0;
}
