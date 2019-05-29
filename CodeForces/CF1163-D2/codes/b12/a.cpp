#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+7;

set<int> F;
int frq[N], rfrq[N];

void add(int val)
{
	--rfrq[frq[val]];
	if(rfrq[frq[val]] == 0) F.erase(frq[val]);

	++frq[val];
	++rfrq[frq[val]];
	F.insert(frq[val]);
}

void remF(int f)
{
	--rfrq[f];
	if(rfrq[f] == 0) F.erase(f);

	--f;

	if(f > 0)
	{
		++rfrq[f];
		F.insert(f);
	}
}

void addF(int f)
{
	--rfrq[f];
	if(rfrq[f] == 0) F.erase(f);

	++f;
	++rfrq[f];
	F.insert(f);
}

#define sz(x) ((int)(x).size())

bool cando()
{
	if(sz(F) > 2) return false;
	if(sz(F) == 1) return (rfrq[*F.begin()] == 1) || (*F.begin() == 1);

	bool res = false;

	auto it = F.begin();
	int f1 = *it, f2;
	it++;
	f2 = *it;

	remF(f1);
	res |= sz(F) == 1;
	addF(f1-1);

	remF(f2);
	res |= sz(F) == 1;
	addF(f2-1);

	return res;
}

int main()
{
  //~ freopen("in", "r", stdin);
	int n;
	scanf("%d", &n);

	int ans = 0;
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d", &x);
		add(x);
		//~ cerr << i << ": ";
		if(cando())
			//~ cerr << "yes",
			ans = i;
		//~ else cerr << "0 ";
		//~ cerr << endl;
	}
	//~ cerr << endl;
	cout << ans << endl;

	return 0;
}
