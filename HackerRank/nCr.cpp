#include<bits/stdc++.h>
using namespace std;

typedef int LL;
typedef double db;
typedef pair<LL,LL> PLL;
typedef vector<LL> VL;

const db PI = acos(-1.);
const db eps = 1e-9;
const LL MOD = 1e9+7;
const LL INF = 1e9+7;
const LL MAXN = 1e6+7;

/********************************************/



///***********************************///
///v              nCr%MOD            v///
///***********************************///

///***********************************///

LL p[MAXN];
inline void sieve(){
    for(LL i=2;i<MAXN;i++){
        if(p[i])continue;
        p[++p[0]]=i;
        for(LL j=i*i;j<MAXN;j+=i)p[j]=i;
    }
}

LL re[222],mo[222],crtcnt;
LL moinv[222],fac[MAXN];

inline void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
    if(!b){d=a;x=1;y=0;}
    else {exgcd(b,a%b,d,y,x);y-=x*(a/b);}
}
inline LL mod_reverse(LL a,LL mod){
    if(!a)return 0;
    LL x,y,d=1;
    exgcd(a,mod,d,x,y);
    x=(x%mod+mod)%mod;
    if(!x)x+=mod;
    return x;
}
inline LL qp(LL a,LL b,LL mod){
    LL res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

inline LL C(LL N,LL R,LL mod){
    if(N<R)return 0;
    LL res=1,i,j,a=1,b=1;
    for(i=1,j=N;i<=R;i++,j--){
        a=a*i%mod;
        b=b*j%mod;
    }
    res=b*mod_reverse(a,mod)%mod;
    //cout<<N<<" "<<R<<" "<<mod<<" "<<b<<" "<<a<<" "<<res<<endl;
    return res;
}
inline LL Lucas(LL N,LL R,LL mod){
    if(R==0)return 1;
    LL res=C(N%mod,R%mod,mod);
    LL tmp=Lucas(N/mod,R/mod,mod)%mod;
    //cout<<N<<" "<<R<<" "<<mod<<"--"<<res<<" "<<tmp<<endl;
    return res=res*tmp%mod;
}

inline LL Div(LL N,LL p){
    LL res=0;
    while(N){
        res+=N/p;
        N/=p;
    }
    return res;
}
inline void get(LL &a,LL N,LL p,LL pk){
    a=1;
    while(N){
        a=a*qp(fac[pk],N/pk,pk)%pk*fac[N%pk]%pk;;
        N/=p;
    }
    //a=a*fac[N]%pk;
}
inline LL exLucas(LL N,LL R,LL p,LL pk){
    if(N<R)return 0;
    LL a=Div(N,p);
    LL b=Div(R,p);
    LL c=Div(N-R,p);
    LL k=a-b-c,i;
    //cout<<a<<" "<<b<<" "<<c<<" "<<k<<": ";
    for(fac[0]=i=1;i<=pk;i++)fac[i]=fac[i-1]*((i%p)?i:1)%pk;
    get(a,N,p,pk);
    get(b,R,p,pk);
    get(c,N-R,p,pk);
    //cout<<a<<" "<<b<<" "<<c<<endl;
    LL euler=pk/p*(p-1);
    if(k>euler)k=k%euler+euler;
    LL res=a*mod_reverse(b*c%pk,pk)%pk*qp(p,k,pk);
    return res;
}

inline void CRT_pre(){
    LL mod=142857, i,j,k,d,x,y;
    exgcd(mod/27,27,d,moinv[1],y);
    exgcd(mod/11,11,d,moinv[2],y);
    exgcd(mod/13,13,d,moinv[3],y);
    exgcd(mod/37,37,d,moinv[4],y);
}
inline LL crt(){
    LL i,res=0,mod=142857;
    for(i=1;i<=4;i++)
        res+=mod/mo[i]*moinv[i]%mod*re[i]%mod;
    return res=(res%mod+mod)%mod;
}

inline LL CRT(LL &res){
    LL i,j,w,Mod=1,d=1,x,y;
    for(i=1;i<=crtcnt;i++)Mod*=mo[i];
    for(i=1;i<=crtcnt;i++){
        w=Mod/mo[i];
        exgcd(w,mo[i],d,x,y);
        res+=re[i]*w%Mod*x%Mod;
    }
    return res=(res%Mod+Mod)%Mod;
}

inline LL nCr(LL N,LL R,LL mod){
    LL i,j,k,pk,res=0;crtcnt=0;
    for(i=1;i<=p[0]&&p[i]*p[i]<=mod;i++){
        if(mod%p[i])continue;
        pk=1;
        while(mod%p[i]==0)pk*=p[i],mod/=p[i];
        crtcnt++;
        if(pk==p[i])
            re[crtcnt]=Lucas(N,R,p[i]);
        else
            re[crtcnt]=exLucas(N,R,p[i],pk);
        mo[crtcnt]=pk;
        //cout<<i<<" : "<<p[i]<<" "<<pk<<" "<<re[crtcnt]<<" "<<mo[crtcnt]<<endl;
    }
    if(mod>1){
        crtcnt++;
        re[crtcnt]=Lucas(N,R,mod);
        mo[crtcnt]=mod;
    }
    //for(i=1;i<=crtcnt;i++)cout<<i<<" : "<<mo[i]<<" "<<re[i]<<endl;
    //CRT(res);
    res=crt();
    return res;
}

///A********************************A///

LL f[MAXN];

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("nCr.in","r",stdin);
    //freopen("nCr.out","w",stdout);
    LL i;
    //for(i=1;i<=100000;i++)cin>>f[i];
    //sieve();
    p[++p[0]]=3;p[++p[0]]=11;p[++p[0]]=13;p[++p[0]]=37;
    CRT_pre();
    LL t,n,r,mod=142857,ca=0,res;
    cin>>t;
    while(t--){
        cin>>n>>r;
        //cout<<"Case#"<<(++ca)<<": "<<n<<" "<<r<<" ";
        //cin>>mod;
        res=nCr(n,r,mod);
        //if(res != f[++ca])cout<<"Case#"<<(ca)<<": "<<n<<" "<<r<<" "<<f[ca]<<" - "<<res<<endl;
        cout<<res<<endl;
    }
    return 0;
}
