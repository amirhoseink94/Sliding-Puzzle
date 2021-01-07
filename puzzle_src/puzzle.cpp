#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include "puzzle.h"
using namespace std;
puzzle::puzzle(int n)
{
	
	t=new int[n*n];
	a=new int*[n];
	for(int i=0;i<n;i++)
		a[i]=t+n*i;
	fillrandom(a,n);
	cout<<endl;
	print(a,n);
	cout<<"do you want to start?(y or n)";
	char jh;
	cin>>jh;
	if(jh=='y')
		solve(a,n,1);
	print(a,n);
}
void puzzle::upload(int** a,const int n)
{
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(a[i][j]==0)
				cout<<setw(3)<<"0";
			else
				if(s[a[i][j]-1]==' ')
					cout<<setw(3)<<"'";
				else
					cout<<setw(3)<<s[a[i][j]-1];
		cout<<endl;
	}
	cout<<endl;
}
void puzzle::fillrandom(int **a,const int n)
{
	int k=1;
	srand(time(0));
	srand(rand());
	srand(rand());
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			a[i][j]=0;
	int p,q;
	while(k<n*n)
	{
		p=rand()%n;q=rand()%n;
		if(a[p][q]==0)
			a[p][q]=k++;
	}
}
int* puzzle::search(int **a,const int n,const int s)
{
	int *an=new int[2];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(a[i][j]==s){
				an[0]=i;
				an[1]=j;
				return an;
				}
}
void puzzle::movezero(const int n,int** a,int* s,int* e)
{	
	if(e[0]-s[0]>0)//down
		for(int i=s[0];i<e[0];i++)
		{
			int t=a[i][e[1]];
			a[i][e[1]]=a[i+1][e[1]];
			a[i+1][e[1]]=t;
			print(a,n);
		}
	if(e[1]-s[1]>0)//right
		for(int i=s[1];i<e[1];i++)
		{
			int t=a[s[0]][i];
			a[s[0]][i]=a[s[0]][i+1];
			a[s[0]][i+1]=t;
			print(a,n);
		}
	if(e[1]-s[1]<0)//left
		for(int i=s[1];i>e[1];i--)
		{
			int t=a[s[0]][i];
			a[s[0]][i]=a[s[0]][i-1];
			a[s[0]][i-1]=t;
			print(a,n);
		}
	if(e[0]-s[0]<0)//up
		for(int i=s[0];i>e[0];i--)
		{
			int t=a[i][e[1]];
			a[i][e[1]]=a[i-1][e[1]];
			a[i-1][e[1]]=t;
			print(a,n);
		}
}
bool puzzle::inreng(const int n,int m){	return (0<=m&&m<n)?true:false;	}
bool puzzle::equality(int*a,int*b){ return (a[0]==b[0]&&a[1]==b[1])?true:false;	}
void puzzle::moveup(int**a,const int n,int* p)
{
	int * z=search(a,n,0);
	if(z[0]<p[0]&&z[1]==p[1])
		movezero(n,a,z,p);
	else if(z[0]>p[0]&&z[1]==p[1])
	{
		if(z[1]==n-1)
		{
			int zp[2]={z[0],z[1]-1};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0]-1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
		else
		{
			int zp[2]={z[0],z[1]+1};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0]-1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
	}
	else if(z[0]==p[0]&&p[1]<z[1])
	{
		int zp[2]={z[0],p[1]+1};
		movezero(n,a,z,zp);
		z=search(a,n,0);
		zp[0]=p[0]-1;
		movezero(n,a,z,zp);
		zp[1]--;
		z=search(a,n,0);
		movezero(n,a,z,zp);
		movezero(n,a,zp,p);
	}
	else if(z[0]==p[0]&&p[1]>z[1])
	{
		if(inreng(n,p[1]+1)&&inreng(n,p[0]+1))
		{
			int zp[2]={z[0],p[1]-1};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0]+1;
			movezero(n,a,z,zp);
			zp[1]+=2;
			z=search(a,n,0);
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]-=2;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]--;
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
		else
		{
			int zp[2]={z[0],p[1]-1};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0]-1;
			movezero(n,a,z,zp);
			zp[1]++;
			z=search(a,n,0);
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
	}
	else
	{
		int zp[2]={n-1,z[1]};
		movezero(n,a,z,zp);
		if(p[0]==n-1)
			moveup(a,n,p);
		else
		{
			zp[1]=p[1];
			z=search(a,n,0);
			movezero(n,a,z,zp);
			moveup(a,n,p);
		}
	}
}
void puzzle::movedown(int**a,const int n,int* p)
{
	int * z=search(a,n,0);
	if(z[0]>p[0]&&z[1]==p[1])
		movezero(n,a,z,p);
	else if(z[0]<p[0]&&z[1]==p[1])
	{
		if(z[1]==n-1)
		{
			int zp[2]={z[0],z[1]-1};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0]+1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
		else
		{
			int zp[2]={z[0],z[1]+1};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0]+1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
	}
	else if(z[0]==p[0]&&z[1]>p[1])
	{
		int zp[2]={z[0],p[1]+1};
		movezero(n,a,z,zp);
		z=search(a,n,0);
		zp[0]=p[0]+1;
		movezero(n,a,z,zp);
		zp[1]--;
		z=search(a,n,0);
		movezero(n,a,z,zp);
		movezero(n,a,zp,p);
	}
	else if(z[0]==p[0]&&z[1]<p[1])
	{
		int zp[2]={z[0],p[1]-1};
		movezero(n,a,z,zp);
		z=search(a,n,0);
		zp[0]=p[0]+1;
		movezero(n,a,z,zp);
		zp[1]++;
		z=search(a,n,0);
		movezero(n,a,z,zp);
		movezero(n,a,zp,p);
	}
	else
	{
		int zp[2]={n-1,z[1]};
		movezero(n,a,z,zp);
		if(p[0]==n-1)
			movedown(a,n,p);
		else
		{
			zp[1]=p[1];
			z=search(a,n,0);
			movezero(n,a,z,zp);
			movedown(a,n,p);
		}
	}
}
void puzzle::moveright(int**a,const int n,int* p)
{
	int * z=search(a,n,0);
	if(z[0]==p[0]&&z[1]>p[1])
		movezero(n,a,z,p);
	else if(z[0]==p[0]&&z[1]<p[1])
	{
		if(z[0]==n-1)
		{
			int zp[2]={z[0]-1,z[1]};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1]+1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
		else
		{
			int zp[2]={z[0]+1,z[1]};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1]+1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
	}
	else if(z[1]==p[1]&&p[0]>z[0])
	{
		int zp[2]={p[0]-1,z[1]};
		movezero(n,a,z,zp);
		z=search(a,n,0);
		zp[1]=p[1]+1;
		movezero(n,a,z,zp);
		zp[0]++;
		z=search(a,n,0);
		movezero(n,a,z,zp);
		movezero(n,a,zp,p);
	}
	else if(z[1]==p[1]&&p[0]<z[0])
	{
		int zp[2]={p[0]+1,z[1]};
		movezero(n,a,z,zp);
		z=search(a,n,0);
		zp[1]=p[1]+1;
		movezero(n,a,z,zp);
		zp[0]--;
		z=search(a,n,0);
		movezero(n,a,z,zp);
		movezero(n,a,zp,p);
	}
	else
	{
		int zp[2]={n-1,z[1]};
		movezero(n,a,z,zp);
		if(p[0]==n-1)
			moveright(a,n,p);
		else
		{
			zp[1]=p[1];
			z=search(a,n,0);
			movezero(n,a,z,zp);
			moveright(a,n,p);
		}
	}
}
void puzzle::moveleft(int**a,const int n,int* p)
{
	int * z=search(a,n,0);
	if(z[0]==p[0]&&z[1]<p[1])
		movezero(n,a,z,p);
	else if(z[0]==p[0]&&z[1]>p[1])
	{
		if(z[0]==n-1)
		{
			int zp[2]={z[0]-1,z[1]};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1]-1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
		else
		{
			int zp[2]={z[0]+1,z[1]};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1]-1;
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[0]=p[0];
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
	}
	else if(z[1]==p[1]&&p[0]>z[0])
	{
		if(inreng(n,p[1]+1)&&inreng(n,p[0]+1))
		{
			int zp[2]={p[0]-1,z[1]};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1]+1;
			movezero(n,a,z,zp);
			zp[0]+=2;
			z=search(a,n,0);
			movezero(n,a,z,zp);
			zp[1]-=2;
			z=search(a,n,0);
			movezero(n,a,z,zp);
			zp[0]--;
			z=search(a,n,0);
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
		else
		{
			int zp[2]={p[0]-1,z[1]};
			movezero(n,a,z,zp);
			z=search(a,n,0);
			zp[1]=p[1]-1;
			movezero(n,a,z,zp);
			zp[0]++;
			z=search(a,n,0);
			movezero(n,a,z,zp);
			movezero(n,a,zp,p);
		}
	}
	else if(z[1]==p[1]&&p[0]<z[0])
	{
		int zp[2]={p[0]+1,z[1]};
		movezero(n,a,z,zp);
		z=search(a,n,0);
		zp[1]=p[1]-1;
		movezero(n,a,z,zp);
		zp[0]--;
		z=search(a,n,0);
		movezero(n,a,z,zp);
		movezero(n,a,zp,p);
	}
	else
	{
		int zp[2]={n-1,z[1]};
		movezero(n,a,z,zp);
		if(p[0]==n-1)
			moveleft(a,n,p);
		else
		{
			zp[1]=p[1];
			z=search(a,n,0);
			movezero(n,a,z,zp);
			moveleft(a,n,p);
		}
	}
}
void puzzle::gotoposition(int**a,const int n,const int m,const int e)
{
	int * u=new int[2];
	if(e==1)
	{
		u[0]=m/n;
		u[1]=m%n-1;
	}
	else
	{
		u[0]=n-1-m/n;
		u[1]=n-1-m%n;
	}
	int *w=search(a,n,m);
	if(w[0]<u[0])
		for(int i=0;i<u[0]-w[0];i++)
		{
			int*wp=search(a,n,m);
			movedown(a,n,wp);
		}
	if(w[1]<u[1])
		for(int i=0;i<u[1]-w[1];i++)
		{
			int*wp=search(a,n,m);
			moveright(a,n,wp);
		}
	if(w[1]>u[1])
		for(int i=0;i<-u[1]+w[1];i++)
		{
			int*wp=search(a,n,m);
			moveleft(a,n,wp);
		}
	if(w[0]>u[0])
		for(int i=0;i<-u[0]+w[0];i++)
		{	
			int*wp=search(a,n,m);
			moveup(a,n,wp);
		}
}
void puzzle::specialpositoin(int**a,const int n,const int m,const int e)
{
	int *u=new int[2];
	int u0;
	if(e==1)
	{
		u[0]=m/n-1;
		u[1]=n-1;
	}
	else
	{
		u[0]=n-1-m/n;
		u[1]=n-1-m%n;
	}
	if(equality(search(a,n,0),u))
	{
		u[0]++;
		movezero(n,a,search(a,n,0),u);
		if(a[u[0]-1][u[1]]==m)
			return;
	}
	if(e==1)
	{
		u[1]=n-1;
		u[0]=m/n-1;
	}
	else
	{
		u[0]=n-1-m/n;
		u[1]=n-1-m%n;
	}
	if(a[u[0]][u[1]]==m)
		return;
	u0=u[0];
	int *w=search(a,n,m);
	u[0]++;
	u[1]--;
	if(w[0]<u[0])
		for(int i=0;i<u[0]-w[0];i++)
		{
			int*wp=search(a,n,m);
			movedown(a,n,wp);
		}
	if(w[1]<u[1])
		for(int i=0;i<u[1]-w[1];i++)
		{
			int*wp=search(a,n,m);
			moveright(a,n,wp);
		}
	if(w[1]>u[1])
		for(int i=0;i<-u[1]+w[1];i++)
		{
			int*wp=search(a,n,m);
			moveleft(a,n,wp);
		}
	if(w[0]>u[0])
		for(int i=0;i<-u[0]+w[0];i++)
		{	
			int*wp=search(a,n,m);
			moveup(a,n,wp);
		}
	w=search(a,n,0);
	u[0]=n-1;
	u[1]=w[1];	
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=n-3;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]=u0;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=w[1]+1;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]--;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=n-3;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]=n-1;
	movezero(n,a,w,u);
}
void puzzle::specialpositoin2(int**a,const int n,const int m,const int e)
{
	int *u=new int[2];
	int u1;
	if(e==1)
	{
		u[1]=m%n-1;
		u[0]=n-1;
	}
	else
	{
		u[0]=n-1;
		u[1]=n-1-m%n;
	}
	if(equality(search(a,n,0),u))
	{
		u[1]++;
		movezero(n,a,search(a,n,0),u);
		if(a[u[0]][u[1]-1]==m)
			return;
	}
	if(e==1)
	{
		u[1]=m%n-1;
		u[0]=n-1;
	}
	else
	{
		u[0]=n-1;
		u[1]=n-1-m%n;
	}
	if(a[u[0]][u[1]]==m)
		return;
	u1=u[1];
	u[0]--;
	u[1]++;
	int*w=search(a,n,m);
	if(w[0]<u[0])
		for(int i=0;i<u[0]-w[0];i++)
		{
			int*wp=search(a,n,m);
			movedown(a,n,wp);
		}
	if(w[1]<u[1])
		for(int i=0;i<u[1]-w[1];i++)
		{
			int*wp=search(a,n,m);
			moveright(a,n,wp);
		}
	if(w[1]>u[1])
		for(int i=0;i<-u[1]+w[1];i++)
		{
			int*wp=search(a,n,m);
			moveleft(a,n,wp);
		}
	if(w[0]>u[0])
		for(int i=0;i<-u[0]+w[0];i++)
		{	
			int*wp=search(a,n,m);
			moveup(a,n,wp);
		}
	w=search(a,n,0);
	u[1]=n-1;
	u[0]=w[0];
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]=n-3;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=u1;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]--;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]=n-3;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=n-1;
	movezero(n,a,w,u);
}
void puzzle::veryspecialmovement(int**a,const int n,const int e)
{
	int *u=new int[2];
	int m;
	if(e==1)
		m=n*n-2;
	else
		m=2;
	u[0]=n-1;
	u[1]=n-3;
	if(equality(search(a,n,0),u))
	{
		u[1]++;
		movezero(n,a,search(a,n,0),u);
		if(a[u[0]][u[1]-1]==m){
			return;
			}
	}
	u[0]=n-1;
	u[1]=n-3;
	if(a[u[0]][u[1]]==m)
		return;	
	u[0]--;
	u[1]++;
	int*w=search(a,n,m);
	if(w[0]<u[0])
		for(int i=0;i<u[0]-w[0];i++)
		{
			int*wp=search(a,n,m);
			movedown(a,n,wp);
		}
	if(w[1]<u[1])
		for(int i=0;i<u[1]-w[1];i++)
		{
			int*wp=search(a,n,m);
			moveright(a,n,wp);
		}
	if(w[1]>u[1])
		for(int i=0;i<-u[1]+w[1];i++)
		{
			int*wp=search(a,n,m);
			moveleft(a,n,wp);
		}
	if(w[0]>u[0])
		for(int i=0;i<-u[0]+w[0];i++)
		{	
			int*wp=search(a,n,m);
			moveup(a,n,wp);
		}
	w=search(a,n,0);
	u[0]=n-1;
	u[1]=w[1];
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=n-1;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]=n-3;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=n-3;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]++;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]--;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]=n-3;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[1]=n-1;
	movezero(n,a,w,u);
	w=search(a,n,0);
	u[0]=n-1;
	movezero(n,a,w,u);
}
bool puzzle::everythingisok(int** a,const int n)
{
	int*t=new int[n*n];
	for(int i=0;i<n*n;i++)
		t[i]=i+1;
	t[n*n-1]=0;
	int**orginal=new int*[n];
	for(int i=0;i<n;i++)
		orginal[i]=t+n*i;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(a[i][j]!=orginal[i][j])
				return false;
	return true;
}
void puzzle::solve(int**a,const int n,const int e)
{
	int*t=new int[n*n];
	if(e==1)
		for(int i=0;i<n*n;i++)
			t[i]=i+1;
	else
		for(int i=0;i<n*n;i++)
			t[i]=n*n-1-i;
	t[n*n-1]=0;
	int**orginal=new int*[n];
	for(int i=0;i<n;i++)
		orginal[i]=t+n*i;
	for(int w=0;w<=n-4;w++)
	{
		for(int i=w;i<=n-2;i++)
			gotoposition(a,n,orginal[w][i],e);
		specialpositoin(a,n,orginal[w][n-1],e);
		for(int i=w+1;i<=n-2;i++)
			gotoposition(a,n,orginal[i][w],e);
		specialpositoin2(a,n,orginal[n-1][w],e);
	}
	for(int i=n-3;i<n-1;i++)
		gotoposition(a,n,orginal[n-3][i],e);
	specialpositoin(a,n,orginal[n-3][n-1],e);
	gotoposition(a,n,orginal[n-2][n-3],e);
	veryspecialmovement(a,n,e);
	if(e==1)
		gotoposition(a,n,n*n-n-1,e);
	else
		gotoposition(a,n,n+1,e);
	int*u=new int[2];
	int*z=search(a,n,0);
	u[0]=n-1;
	u[1]=z[1];
	movezero(n,a,z,u);
	z[0]=u[0];
	z[1]=u[1];
	u[1]=n-1;
	movezero(n,a,z,u);
	if(e==1){
		int hope=ishope(a,n);
		if(hope!=-1)
			rollingzero(a,n,(3-hope)%3);
		else if(n%2==0){
			print(a,n);
			cout<<"there is another solotion for this test case,do you want to continue?(y or n)";
			char jh;
			cin>>jh;
			if(jh=='y')
				solve(a,n,-1);
		}
		else
			cout<<"there is no normall solotion for this test case.sorry!:("<<endl;
	}
}
int puzzle::ishope(int**a,const int n)
{
	int b[3]={a[n-2][n-2],a[n-2][n-1],a[n-1][n-2]};
	for(int i=0;i<3;i++)//{
		if(b[i%3]<b[(i+1)%3]&&b[(i+1)%3]<b[(i+2)%3])
			return i;
	return -1;	
}
void puzzle::rollingzero(int**a,const int n,const int m)
{
	int*z=new int[2];
	z[0]=n-1;z[1]=n-1;
	for(int i=0;i<m;i++)
	{
		int*u=new int[2];
		u[0]=n-2;
		u[1]=n-1;
		z[0]=n-1;
		z[1]=n-1;
		movezero(n,a,z,u);
		z[0]=u[0];
		z[1]=u[1];
		u[1]--;
		movezero(n,a,z,u);
		z[0]=u[0];
		z[1]=u[1];
		u[0]++;
		movezero(n,a,z,u);
		z[0]=u[0];
		z[1]=u[1];
		u[1]++;
		movezero(n,a,z,u);
	}
}
void puzzle::print(int**a,const int n)
{
	//upload(a,n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cout<<setw(5)<<a[i][j];
		cout<<endl;
	}
	cout<<endl;
}
