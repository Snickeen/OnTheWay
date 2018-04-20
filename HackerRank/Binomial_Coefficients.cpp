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

//>>>>>>>>>>>>>>>>>BigNum>>>>>>>>>>>>>>>>>>>>>>>
/*
* 完全大数模板
* 输出cin>>a
* 输出a.print();
* 注意这个输入不能自动去掉前导0的，可以先读入到char数组，去掉前导0，再用构造函数。
*/
typedef int INT
#define MAXB 9999
#define MAXSIZE 1010
#define DLEN 4

class BigNum{
private:
	INT a[500]; //可以控制大数的位数
	INT len;
public:
	BigNum(){len=1;memset(a,0,sizeof(a));}; //构造函数
	BigNum(const INT); //将一个INT类型的变量转化成大数
	BigNum(const char*); //将一个字符串类型的变量转化为大数
	BigNum(const BigNum &); //拷贝构造函数
	BigNum &operator=(const BigNum &); //重载赋值运算符，大数之间进行赋值运算
	friend istream& operator>>(istream&,BigNum&); //重载输入运算符
	friend ostream& operator<<(ostream&,BigNum&); //重载输出运算符

	BigNum operator+(const BigNum &)const; //重载加法运算符，两个大数之间的相加运算
	BigNum operator-(const BigNum &)const; //重载减法运算符，两个大数之间的相减运算
	BigNum operator*(const BigNum &)const; //重载乘法运算符，两个大数之间的相乘运算
	BigNum operator/(const INT &)const; //重载除法运算符，大数对一个整数进行相除运算

	BigNum operator^(const INT &)const; //大数的n次方运算
	INT operator%(const INT &)const; //大数对一个INT类型的变量进行取模运算
	bool operator>(const BigNum &T)const; //大数和另一个大数的大小比较
	bool operator>(const INT &t)const; //大数和一个INT类型的变量的大小比较

	void print(); //输出大数
};
//将一个INT类型的变量转化为大数
BigNum::BigNum(const INT b){
	INT c,d=b;
	len=0;
	memset(a,0,sizeof(a));
	while(d>MAXB){
		c=d-(d/(MAXB+1))*(MAXB+1);
		d=d/(MAXB+1);
		a[len++]=c;
	}
	a[len++]=d;
}
//将一个字符串类型的变量转化为大数
BigNum::BigNum(const char *s) {
	INT t,k,index,L,i;
	memset(a,0,sizeof(a));
	L=strlen(s);
	len=L/DLEN;
	if(L%DLEN)len++;
	index=0;
	for(i=L-1;i>=0;i-=DLEN){
		t=0;
		k=i-DLEN+1;
		if(k<0)k=0;
		for(INT j=k;j<=i;j++)
			t=t*10+s[j]-'0';
		a[index++]=t;
	}
}
//拷贝构造函数
BigNum::BigNum(const BigNum &T):len(T.len){
	INT i;
	memset(a,0,sizeof(a));
	for(i=0;i<len;i++)
		a[i]=T.a[i];
}
//重载赋值运算符，大数之间赋值运算
BigNum & BigNum::operator=(const BigNum &n){
	INT i;
	len=n.len;
	memset(a,0,sizeof(a));
	for(i=0;i<len;i++)
		a[i]=n.a[i];
	return *this;
}
//重载输入运算符
istream& operator>>(istream &in,BigNum &b){
	char ch[MAXSIZE*4];
	INT i=-1;
	in>>ch;
	INT L=strlen(ch);
	INT count=0,sum=0;
	for(i=L-1;i>=0;){
		sum=0;
		INT t=1;
		for(INT j=0;j<4&&i>=0;j++,i--,t*=10){
			sum+=(ch[i]-'0')*t;
		}
		b.a[count]=sum;
		count++;
	}
	b.len=count++;
	return in;
}
//重载输出运算符
ostream& operator<<(ostream& out,BigNum& b) {
	INT i;
	cout<<b.a[b.len-1];
	for(i=b.len-2;i>=0;i--){
		printf("%04d",b.a[i]);
	}
	return out;
}
//两个大数之间的相加运算
BigNum BigNum::operator+(const BigNum &T)const{
	BigNum t(*this);
	INT i,big;
	big=T.len>len?T.len:len;
	for(i=0;i<big;i++){
		t.a[i]+=T.a[i];
		if(t.a[i]>MAXB){
			t.a[i+1]++;
			t.a[i]-=MAXB+1;
		}
	}
	if(t.a[big]!=0)
		t.len=big+1;
	else t.len=big;
	return t;
}
//两个大数之间的相减运算
BigNum BigNum::operator-(const BigNum &T)const{
	INT i,j,big;
	bool flag;
	BigNum t1,t2;
	if(*this>T){
		t1=*this;
		t2=T;
		flag=0;
	}
	else{
		t1=T;
		t2=*this;
		flag=1;
	}
	big=t1.len;
	for(i=0;i<big;i++){
		if(t1.a[i]<t2.a[i]){
			j=i+1;
			while(t1.a[j]==0)
				j++;
			t1.a[j--]--;
			while(j>i)
				t1.a[j--]+=MAXB;
			t1.a[i]+=MAXB+1-t2.a[i];
		}
		else t1.a[i]-=t2.a[i];
	}
	t1.len=big;
	while(t1.a[len-1]==0 && t1.len>1){
		t1.len--;
		big--;
	}
	if(flag)
		t1.a[big-1]=0-t1.a[big-1];
	return t1;
}
//两个大数之间的相乘
BigNum BigNum::operator*(const BigNum &T)const{
	BigNum ret;
	INT i,j,up;
	INT temp,temp1;
	for(i=0;i<len;i++){
		up=0;
		for(j=0;j<T.len;j++){
			temp=a[i]*T.a[j]+ret.a[i+j]+up;
			if(temp>MAXB){
				temp1=temp-temp/(MAXB+1)*(MAXB+1);
				up=temp/(MAXB+1);
				ret.a[i+j]=temp1;
			}
			else{
				up=0;
				ret.a[i+j]=temp;
			}
		}
		if(up!=0)
		ret.a[i+j]=up;
	}
	ret.len=i+j;
	while(ret.a[ret.len-1]==0 && ret.len>1)ret.len--;
	return ret;
}
//大数对一个整数进行相除运算
BigNum BigNum::operator/(const INT &b)const {
	BigNum ret;
	INT i,down=0;
	for(i=len-1;i>=0;i--){
		ret.a[i]=(a[i]+down*(MAXB+1))/b;
		down=a[i]+down*(MAXB+1)-ret.a[i]*b;
	}
	ret.len=len;
	while(ret.a[ret.len-1]==0 && ret.len>1)
	ret.len--;
	return ret;
}
//大数对一个 INT类型的变量进行取模
INT BigNum::operator%(const INT &b)const{
	INT i,d=0;
	for(i=len-1;i>=0;i--)
		d=((d*(MAXB+1))%b+a[i])%b;
	return d;
}
//大数的n次方运算
BigNum BigNum::operator^(const INT &n)const{
	BigNum t,ret(1);
	INT i;
	if(n<0)exit(-1);
	if(n==0)return 1;
	if(n==1)return *this;
	INT m=n;
	while(m>1){
		t=*this;
		for(i=1;(i<<1)<=m;i<<=1)
			t=t*t;
		m-=i;
		ret=ret*t;
		if(m==1)ret=ret*(*this);
	}
	return ret;
}
//大数和另一个大数的大小比较
bool BigNum::operator>(const BigNum &T)const {
	INT ln;
	if(len>T.len)return true;
	else if(len==T.len){
		ln=len-1;
		while(a[ln]==T.a[ln]&&ln>=0)
			ln--;
		if(ln>=0 && a[ln]>T.a[ln])
			return true;
		else
			return false;
	}
	else
		return false;
}
//大数和一个INT类型的变量的大小比较
bool BigNum::operator>(const INT &t)const{
	BigNum b(t);
	return *this>b;
}
//输出大数
void BigNum::print(){
	INT i;
	printf("%d",a[len-1]);
	for(i=len-2;i>=0;i--)
		printf("%04d",a[i]);
	printf("\n");
}
//<<<<<<<<<<<<<<BigNum<<<<<<<<<<<<<<<<<<<<<<<<<<<

LL t,p;
BigNum_ ans,n,res;

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);//cout<<fixed<<setprecision(9);
    cin>>t;
    while(t--){
        cin>>n>>p;
        if(n<2){
            cout<<"0"<<endl;
            continue;
        }
        ans=n+1;
        res=1;
        while(n>0){
            res*=n%p+1;
        }
        ans-=res;
        ans.print();
    }
    return 0;
}
