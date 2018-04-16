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
const LL MAXN = 1e5+7;

/******************************************************/

bitset<MAXN> prime;
LL p[MAXN/10]; // p[0] counts primes.
inline void GetPrime(){
    LL i,j,k;
    prime[0]=prime[1]=1;p[0]=0;
    for(i=2;i<MAXN;i++){
        if(prime[i])continue;
        p[++p[0]]=i;
        for(j=i+i;j<MAXN;j+=i)prime[j]=1;
    }
}

/*******************************************/
//PrimitiveRoot: to all FactorOfPhiP --> g^(PhiP/FactorOfPhiP) != 1 (mod P)
//the number of primitive root of P is phi(phi(P))
vector<LL> PrimitiveRoot,FactorOfPhiP;
LL PhiP, NumberOfPrimitiveRoot;
inline LL GetPhiP(LL _P){
    LL i,res=_P,_P_=(LL)floor(sqrt(1.0*_P));
    for(i=1;p[i]<=_P_;i++){
        if(_P%p[i]==0){
            res=res/p[i]*(p[i]-1);
            while(_P%p[i]==0)_P/=p[i];
        }
    }
    if(_P>1)res=res/_P*(_P-1);
    return res;
}
inline void GetFactorOfPhiP(LL phip){
    FactorOfPhiP.clear();
    LL _P_=(LL)floor(sqrt(1.0*phip));
    for(LL i=1;p[i]<=_P_;i++){
        if(phip%p[i]==0){
            FactorOfPhiP.push_back(p[i]);
            while(phip%p[i]==0)phip/=p[i];
        }
    }
    if(phip>1)FactorOfPhiP.push_back(phip);
}
inline LL quickpow(LL a,LL b,LL mod){
    LL res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
inline LL GetPrimitiveRoot(LL P){
    PhiP=GetPhiP(P);
    NumberOfPrimitiveRoot=GetPhiP(PhiP);//The number of primitive root
    GetFactorOfPhiP(PhiP);
    //PrimitiveRoot.clear();
    LL g,i,flag,l=FactorOfPhiP.size();
    for(g=2;g<PhiP;g++){
        flag=1;
        for(i=0;i<l;i++){
            if(quickpow(g,PhiP/FactorOfPhiP[i],P) == 1){
                flag=0;
                break;
            }
        }
        if(flag){
            //PrimitiveRoot.push_back(g);
            break;
        }
    }
    return g;//the smallest g
}

/*******************************************/

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);//cout<<fixed<<setprecision(9);
    LL p,g,sz;
    cin>>p;
    GetPrime();//if you do not want to do it, it's also OK.
    g=GetPrimitiveRoot(p);//the smallest primitive root g
    sz=NumberOfPrimitiveRoot;// the number of primitive root of P if phi(phi(P))
    cout<<g<<" "<<sz<<endl;
    return 0;
}
