/*
Author: Snickeen.
Email : ff@snickeen.com

If you find some bugs, please tell me. Thank you.
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double db;
typedef pair<LL,LL> PLL;

const db PI = acos(-1.0);
const db eps = 1e-9;
const LL MOD = 1e9+7;
const LL INF = 1e18+7;
const LL MAXN = 1e6+7;

/******************************************************/

LL p[MAXN],p2[MAXN],p2cnt;
inline void getprime(){
    for(LL i=2;i<MAXN;i++){
        if(p[i])continue;
        p[++p[0]]=i;
        for(LL j=i+i;j<MAXN;j+=i)p[j]=1;
    }
}

inline void getprime2(LL L,LL R){
    for(LL i=1;i<=p[0]&&p[i]*p[i]<=R;i++){
        LL s=L/p[i]+(L%p[i]>0);
        if(s==1)s=2;
        for(LL j=s;j*p[i]<=R;j++)if(j*p[i]>=L)p2[j*p[i]-L]=1;
    }
    p2cnt=0;
    //for(LL i=0;i<=m-n;i++)if(!p2[i])p2[p2cnt++]=i+L;
}

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);//cout<<fixed<<setprecision(9);
    LL n,m,i,a=1,b,ans=0;
    getprime();
    cin>>n>>m;
    if(n<3)n=3;
    getprime2(n,m);
    for(i=2;i+n<=m;i++)
        ans+=(p2[i-2]+p2[i]==0);
    cout<<ans<<endl;
    return 0;
}
