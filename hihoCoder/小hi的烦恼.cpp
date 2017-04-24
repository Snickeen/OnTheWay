/*
By Snickeen.
*/
#include<bits/stdc++.h>
using namespace std;

int t,n,m,ans,tot;
bitset<30002> g[30002][5];
struct NODE{
	int a;
	int idx;
};
NODE node[5][30002];

int cmp(NODE a,NODE b){return a.a<b.a;}

int main()
{
	int i,j,k,l,ca=0;
//	printf("%d\n",(30000*30000*5/8+30002*5*2*4)/1024/1024);
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		for(j=0;j<5;j++)scanf("%d",&node[j][i].a),node[j][i].idx=i;
	for(i=0;i<5;i++){
		sort(node[i]+1,node[i]+n+1,cmp);
		for(j=2;j<=n;j++){
			int u=node[i][j].idx;
			int v=node[i][j-1].idx;
			g[u][i]=g[v][i];
			g[u][i][v]=(node[i][j-1].a<node[i][j].a);
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<5;j++)g[i][0]&=g[i][j];
		printf("%d\n",g[i][0].count());
	}
	return 0;
}
