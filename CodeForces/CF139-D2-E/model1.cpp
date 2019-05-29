#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define F first
#define S second
using namespace std;
const int maxn=400010;
pii a[maxn],b[maxn]; int tot,cnt[110];
double qpow(double a,int x){
	double res=1.0; while(x){
		if(x&1) res=res*a;
		a=a*a; x>>=1;
	}return res;
}
int main()
{
	int N,M,i,j,A,H,L,R;
	scanf("%d%d",&N,&M);
	rep(i,1,N){
		scanf("%d%d%d%d",&A,&H,&L,&R);
		b[++tot]=mp(A-H,L);  b[++tot]=mp(A,-L); //左闭右开 
		b[++tot]=mp(A+1,R);  b[++tot]=mp(A+H+1,-R);
	}
	rep(i,1,M) scanf("%d%d",&a[i].F,&a[i].S);
	sort(a+1,a+M+1); sort(b+1,b+tot+1);
	double ans=0; int pos=1;
	rep(i,1,M){
		while(pos<=tot&&b[pos].F<=a[i].F){
			if(b[pos].S>0) cnt[b[pos].S]++;
			if(b[pos].S<0) cnt[-b[pos].S]--;
			pos++;
		}
		double p=a[i].S;
		rep(j,1,100) p*=qpow(0.01*(100-j),cnt[j]);
		ans+=p;
	}
	printf("%.12lf\n",ans);
	return 0; 
}
