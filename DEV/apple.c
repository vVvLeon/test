#include<stdio.h>
int main()
{
 int m,t,s;
 scanf("%d %d %d",&m,&t,&s);

	 if(t==0)
	 {
	 	printf("0");
	 	return 0;
	 }
	 if(s<t)
     {
		printf("%d",m-1);
		
     }
     int n=s/t;
	 if(n>=m)
	 {
	 	printf("0");
	 }
	 else
	 {
	 	if(s%t==0)
	 	{
		printf("%d",m-n);
		}
		else
		{
		n++;
		printf("%d",m-n);
		}

	 }
 return 0;
}
