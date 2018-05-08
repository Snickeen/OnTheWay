/*
Author: Snickeen.
Email : ff@snickeen.com

If you find out some bugs, please tell me. Thank you.
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

LL T,N,R,M,ans;

const LL PN=111;
LL p[PN];
inline void sieve(){
    LL i,j;
    for(i=2;i<PN;i++){
        if(p[i])continue;
        p[++p[0]]=i;
        for(j=i*i;j<PN;j+=i)p[j]=1;
    }
}

inline void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
    if(!b){d=a;x=1;y=0;}
    else {exgcd(b,a%b,d,y,x);y-=x*(a/b);}
}
inline LL mod_reverse(LL a,LL mod){
    LL x,y,d=1;
    exgcd(a,mod,d,x,y);
    return (x%mod+mod)%mod;
}
inline LL qp(LL a,LL b,LL mod){
    LL res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return 0;
}

inline LL C(LL n,LL m,LL mod){
    if(n<m)return 0;
    LL res=1,i,j,a=1,b=1;
    for(i=1,j=n;i<=m;i++,j--){
        a=a*i%mod;
        b=b*j%mod;
    }
    //return res=b*qp(a,mod-2,mod)%mod;
    return res=b*mod_reverse(a,mod)%mod;
}
inline LL Lucas(LL n,LL r,LL mod){
    if(r==0)return 1;
    return C(n%mod,r%mod,mod)*Lucas(n/mod,r/mod,mod)%mod;
}


inline LL CRT(LL fm[],LL r[],LL cnt){
    LL i,mod=1,d,y,x=0,w,res=0;
    for(i=1;i<=cnt;i++)mod*=fm[i];
    for(i=1;i<=cnt;i++){
        w=mod/fm[i];
        exgcd(w,fm[i],d,x,y);
        (res+=x*w*r[i]%mod)%=mod;
    }
    return (res%mod+mod)%mod;
}

LL FactorOfMod[PN],fmcnt,Remainder[PN];
inline LL nCr(LL n,LL r,LL mod){
    LL i,j,k,l,res;
    fmcnt=0;
    for(i=1;i<=p[0]&&p[i]*p[i]<=mod;i++){
        if(mod%p[i])continue;
        FactorOfMod[++fmcnt]=p[i];
        while(mod%p[i]==0)mod/=p[i];
    }
    if(mod>1)FactorOfMod[++fmcnt]=mod;
    for(i=1;i<=fmcnt;i++)Remainder[i]=Lucas(n,r,FactorOfMod[i]);
    res=CRT(FactorOfMod,Remainder,fmcnt);
    return res;
}

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);//cout<<fixed<<setprecision(9);
    sieve();
    cin>>T;
    while(T--){
        cin>>N>>R>>M;
        cout<<nCr(N,R,M)<<endl;
    }
    return 0;
}
