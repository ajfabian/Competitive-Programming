#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> point;
#define F first
#define S second



int main()
{
	#ifdef DGC
		//freopen("a.txt", "r", stdin);
		//freopen("out.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;

	int ans = 1<<30, w;
	for (int k = 2; k < 100; ++k)
	{
		int c = 0;
		for (auto i : a)
		{
			c += min({ abs(k-i), abs(k+1-i), abs(k-1-i) });
		}
		if (c < ans)
			ans = c, w = k;
	}

	cout << w << " " << ans << "\n";

	return 0;
}
