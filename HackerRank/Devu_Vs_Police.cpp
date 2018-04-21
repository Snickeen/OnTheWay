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

LL n1,k1,n2,k2,n,phi,a,b,ans;

inline LL qp(LL x,LL y,LL mod,LL &flag){
    LL res=1;x%=mod;
    while(y){
        if(y&1){
            res=res*x;
            //the key
            if(res%mod != res){
                res%=mod;
                flag=1;
            }
        }
        x=x*x;
        //the key
        if(x%mod!=x){
            x%=mod;
            flag=1;
        }
        y>>=1;
    }
    return res;
}

inline LL getphi(LL x){
    LL res=x;
    for(LL i=2;i*i<=x;i++){
        if(x%i==0){
            res=res/i*(i-1);
            while(x%i==0)x/=i;
        }
    }
    if(x>1)res=res/x*(x-1);
    return res;
}

inline void solve(){
    cin>>n1>>k1>>n2>>k2>>n;
    phi=getphi(n)*100;//the key
    LL tag=0,tagtmp;//the key
    b=qp(n2,k2,phi,tag);
    a=qp(n1,k1,n,tagtmp);
    ans=qp(a,b+phi*(tag!=0),n,tagtmp);//the key
    if(n==1)ans=0;
    cout<<ans<<endl;
}

signed main()
{
    //freopen("Devu Vs Police.myout","w",stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);//cout<<fixed<<setprecision(9);
    LL t;cin>>t;while(t--)solve();
    return 0;
}
