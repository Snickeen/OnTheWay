#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;
typedef unsigned long long ll;
typedef double db;
typedef pair<LL,LL> PLL;
typedef vector<LL> VL;

#define all(x) (x).begin(),(x).end()

const db PI = acos(-1.0);
const db eps = 1e-9;
const LL INF = 1e18+7;
const LL MOD = 1e9+7;
const LL INV2 = 500000004ll;
const LL MAXN = 1e6+7;

/**********************************/

//****************************************************************
// Miller_Rabin 算法进行素数测试
//速度快，而且可以判断 <2^63的数
//****************************************************************
const int S=20;//随机算法判定次数，S越大，判错概率越小


//计算 (a*b)%c.   a,b都是ll的数，直接相乘可能溢出的
//  a,b,c <2^63
ll mult_mod(ll a,ll b,ll c)
{
    a%=c;
    b%=c;
    ll ret=0;
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
ll pow_mod(ll x,ll n,ll mod)//x^n%c
{
    if(n==1)return x%mod;
    x%=mod;
    ll tmp=x;
    ll ret=1;
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
bool check(ll a,ll n,ll x,ll t)
{
    ll ret=pow_mod(a,x,n);
    ll last=ret;
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

bool Miller_Rabin(ll n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;//偶数
    ll x=n-1;
    ll t=0;
    while((x&1)==0){x>>=1;t++;}
    for(int i=0;i<S;i++)
    {
        ll a=rand()%(n-1)+1;//rand()需要stdlib.h头文件
        if(check(a,n,x,t))
            return false;//合数
    }
    return true;
}


//************************************************
//pollard_rho 算法进行质因数分解
//************************************************
ll factor[100];//质因数分解结果（刚返回时是无序的）
int tol;//质因数的个数。数组小标从0开始

ll gcd(ll a,ll b)
{
    if(a==0)return 1;//???????
    if(a<0) return gcd(-a,b);
    while(b)
    {
        ll t=a%b;
        a=b;
        b=t;
    }
    return a;
}

ll Pollard_rho(ll x,ll c)
{
    ll i=1,k=2;
    ll x0=rand()%x;
    ll y=x0;
    while(1)
    {
        i++;
        x0=(mult_mod(x0,x0,x)+c)%x;
        ll d=gcd(y-x0,x);
        if(d!=1&&d!=x) return d;
        if(y==x0) return x;
        if(i==k){y=x0;k+=k;}
    }
}
//对n进行素因子分解
void findfac(ll n)
{
    if(Miller_Rabin(n))//素数
    {
        factor[tol++]=n;
        return;
    }
    ll p=n;
    while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
    findfac(p);
    findfac(n/p);
}

bitset<MAXN> pr;
LL p[MAXN];
signed main()
{
    srand(time(NULL));
    int T;
    ll n;
    pr[0]=pr[1]=1;
    for(LL i=2;i<MAXN;i++){
        if(!pr[i]) p[++p[0]]=i;
        //for(LL j=i*i;j<MAXN;j+=i)pr[j]=1;
        for(ll j=1; j<=p[0] && p[j]*i<MAXN; j++)
        {
        	pr[p[j]*i]=1;
        	if(i%p[j]==0) break;
		}
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%llu",&n);
		for(LL i=1;i<=p[0];i++){
			LL m = n-p[i];
	        if(m<MAXN-10){//O1

	        	if( !pr[m] )
	        	{
	        		printf("%llu %llu\n",p[i],m);
	            	break;
				}
	        }
        	else
        	{

        		LL k=Miller_Rabin(n-p[i]);

		        if(k){
		            printf("%llu %llu\n",p[i],n-p[i]);
		            break;
				}
	        }
        }
    }
    return 0;
}
