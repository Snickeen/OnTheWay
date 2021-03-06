//#include<bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <bitset>
#include <functional>
using namespace std;
typedef int LL;
typedef unsigned long long ULL;
typedef double db;
typedef long double ldb;
#define rep(i,a,b) for(i=a;i<b;i++)
#define repu(i,a,b) for(i=a;i<=b;i++)
#define repd(i,a,b) for(i=a;i>=b;i--)
#define repc(i,a,b,c) for(i=a;i<b;i+=c)
#define repcu(i,a,b,c) for(i=a;i<=b;i+=c)
#define repcd(i,a,b,c) for(i=a;i>=b;i-=c)
#define FIN freopen("input.in","r",stdin)
#define FOUT freopen("output.out","w",stdout)
#define CC(a) memset(a,0,sizeof(a))
#define MST(a,b) memset(a,b,sizeof(a))
#define PII pair<int,int>
#define PLL pair<LL,LL>
#define VI vector<int>
#define VII vector<PII>
#define VLL vector<PLL>
#define all(x) x.begin(),x.end()
#define mp make_pair
#define pb push_back
#define pf push_front
#define fi first
#define se second

template<typename T>inline void gn(T &x){
	x=0;T f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
template<typename T>inline void gt(T x){
	if(!x)return;
	gt(x/10);putchar(x%10+'0');
}

const LL N=203;
struct NODE{
	db x,y;
}ff[N];
LL t,n,m,ans;
LL MOD=1e9+7,inf=0x1f1f1f1f;
db dis[N],g[N][N];
char vis[N];

db getdis(db x,db y){
	return sqrt(x*x+y*y);
}

void dijkstra(){
	LL i,j,k,l,mark,mindis;
	for(i=1;i<=n;i++){
		mark=-1;mindis=1e9;
		for(j=1;j<=n;j++){
			if(!vis[j]&&dis[j]<mindis){
				mindis=dis[j];
				mark=j;
			}
		}
		vis[mark]=1;
		for(j=1;j<=n;j++)if(!vis[j])dis[j]=min(dis[j],max(dis[mark],g[mark][j]));
	}
}

int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);
	LL i,j,k,l,r,ca=0;
//	cout.precision(3);cout<<fixed;
	cout<<fixed<<setprecision(3);
	while(cin>>n,n){
		for(i=0;i<N;i++){
			dis[i]=1e9;vis[i]=0;
			for(j=0;j<N;j++)g[i][j]=1e9;
		}dis[1]=0;
		
		for(i=1;i<=n;i++)cin>>ff[i].x>>ff[i].y;
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				g[i][j]=g[j][i]=min(g[l][i],getdis(ff[i].x-ff[j].x,ff[i].y-ff[j].y));
			}
		}
		dijkstra();
		if(ca)cout<<endl;
		cout<<"Scenario #"<<(++ca)<<endl;
		cout<<"Frog Distance = "<<dis[2]<<endl; 
	}
	return 0;
}
