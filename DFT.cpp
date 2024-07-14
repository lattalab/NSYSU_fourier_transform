#include <iostream>
#include <cmath>
#define pi acos(-1)
using namespace std;
int main()
{
	double x[200],xr[200]={0},xi[200]={0},amp;
	double dt=6/200.0; //取樣週期
	cout<<"The example function: f(x)=10sin(2pi*x)+2sin(16pi*x)\n";
	for(int i=0;i<200;i++)//sampling
	{
		x[i]=10*sin(2*pi*dt*(i+1))+2*sin(16*pi*dt*(i+1));
	}
	
	for(int i=0;i<200;i++) //DFT processing 
	{
		for(int j=0;j<200;j++)
		{
			double angle=2*pi*i*j/200;
			xr[i]+=x[j]*cos(angle);
			xi[i]-=x[j]*sin(angle);
		}
		xr[i]/=200;xi[i]/=200;
		amp=sqrt(xr[i]*xr[i]+xi[i]*xi[i]);
		if(amp>0.5)
		cout<<"明顯的峰值:"<<amp<<endl;
	}
	return 0;
}
