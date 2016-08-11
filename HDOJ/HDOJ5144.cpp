#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;
typedef long long LL;
typedef double db;
#define CC(a) memset(a,0,sizeof(a))
#define FIN freopen("in.txt","r",stdin)
#define FOUT freopen("out.txt","w",stdout)

int t,n,num;
db t1,t2,a,b,c,d,h,v,vx,vy,x,H,ans;
db PI=acos(-1.0),g=9.80,eps=1e-8,eps2=1e-10;

db get(db s){
	int i,j,k,l,cnt,tmp;
	vx=v*cos(s);vy=v*sin(s);
	t1=vy/g;
	h=0.5*vy*t1;
	x=vx*t1;
	t2=sqrt((h+H)*2.0/g);
	x+=vx*t2;
	return x;
}

db ts(){
	int i,j,k,l,tmp,res;
	db L=0.0,R=PI/2.0,lm,rm;
	while(R-L>eps){
		lm=L+(R-L)/3;
		rm=R-(R-L)/3;
		if(get(lm)>get(rm)){
			R=rm;
		}
		else L=lm;
	}
	return R;
}

/*
//bs  eps=1e-7~1e-9  eps2=1e-8~1e10   
尝试通过的具体情况： 
eps=1e-7  eps2=1e-8
eps=1e-7  eps2=1e-9
eps=1e-7  eps2=1e-10
eps=1e-8  eps2=1e-9
eps=1e-8  eps2=1e-10
eps=1e-9  eps2=1e-10
*/
db bs(){
	int i,j,k,l,tmp,res;
	db L=0.0,R=PI/2.0,lm,rm,m;
	while(R-L>eps){
		m=L+(R-L)/2.0;
		if(get(m+eps2)>get(m-eps2)){
			L=m+eps2;
		}
		else R=m-eps2;
	}
	return L;
}

int main()
{
	int i,j,k,l,cnt,tmp;
	double tsnum,tsans,bsnum,bsans;
	scanf("%d",&t);
	while(t--){
		scanf("%lf%lf",&H,&v);
		ans=0;tsnum=ts();tsans=get(tsnum);
		ans=0;bsnum=bs();bsans=get(bsnum);
//		printf("%.9lf %.9lf\n%.9lf %.9lf  ",tsnum,tsans,bsnum,tsans);
		printf("%.2lf\n",bsans);
	}
	return 0;
}
