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

LL p[MAXN+10];
char notp[MAXN+10];

inline void GetPrime(){
    notp[0]=notp[1]=1;p[0]=0;
    for(LL i=2;i<MAXN;i++){
        if(notp[i])continue;
        p[++p[0]]=i;
        for(LL j=i*i;j<MAXN;j+=i)notp[j]=1;
    }
    //cout<<p[0]<<endl;
    //for(LL i=1;i<10;i++)cout<<i<<" "<<p[i]<<endl;
}

inline LL IsPrime(LL x){
    //if(x<MAXN)return !notp[x];
    if(x<2)return 0;
    for(LL i=1;i<=p[0]&&p[i]*p[i]<=x;i++){
        if(x%p[i]==0)return 0;
    }
    return 1;
}



//>>>>>>>>>>>>>>>>>>>Miller_Rabin()>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//****************************************************************
// Miller_Rabin 算法进行素数测试
//速度快，而且可以判断 <2^63的数
//****************************************************************

typedef unsigned long long MRLL;
const int S=10;//随机算法判定次数，S越大，判错概率越小

//计算 (a*b)%c.   a,b都是ll的数，直接相乘可能溢出的
//  a,b,c <2^63
MRLL mult_mod(MRLL a,MRLL b,MRLL c)
{
    a%=c;
    b%=c;
    MRLL ret=0;
    while(b)
    {
        if(b&1){ret+=a;ret%=c;}
        a<<=1;
        if(a>=c)a%=c;
        b>>=1;
    }
    return ret;
}

//计算  x^n %c
MRLL pow_mod(MRLL x,MRLL n,MRLL mod)//x^n%c
{
    if(n==1)return x%mod;
    x%=mod;
    MRLL tmp=x;
    MRLL ret=1;
    while(n)
    {
        if(n&1) ret=mult_mod(ret,tmp,mod);
        tmp=mult_mod(tmp,tmp,mod);
        n>>=1;
    }
    return ret;
}

//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true,不一定返回false
bool check(MRLL a,MRLL n,MRLL x,MRLL t)
{
    MRLL ret=pow_mod(a,x,n);
    MRLL last=ret;
    for(int i=1;i<=t;i++)
    {
        ret=mult_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return true;//合数
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}

// Miller_Rabin()算法素数判定
//是素数返回true.(可能是伪素数，但概率极小)
//合数返回false;

bool Miller_Rabin(MRLL n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;//偶数
    MRLL x=n-1;
    MRLL t=0;
    while((x&1)==0){x>>=1;t++;}
    for(int i=0;i<S;i++)
    {
        MRLL a=rand()%(n-1)+1;//rand()需要stdlib.h头文件
        if(check(a,n,x,t))
            return false;//合数
    }
    return true;
}
//<<<<<<<<<<<<<<<Miller_Rabin()<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



inline LL IsSumOfKNumbers(LL N,LL K){
    LL ans;
    if(N<2*K || K<0)ans=0;
    else if(K==1)ans=Miller_Rabin(N);
    else if(K==2){
        if(N%2==0)ans=1;
        else ans=Miller_Rabin(N-2);
    }
    else ans=1;
    return ans;
}

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);//cout<<fixed<<setprecision(9);
    LL t,n,k,ans;
    GetPrime();
    cin>>t;
    while(t--){
        cin>>n>>k;
        ans=IsSumOfKNumbers(n,k);
        cout<<(ans?"Yes":"No")<<endl;
    }
    return 0;
}
