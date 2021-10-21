#include<stdio.h>
#include<string.h>
void main()
{
char vehicleno[100]={'\0'};
int i,k=0;
char a;
int count=0;
int flag=0;
while((a=getchar())!='\n')
{
	vehicleno[k]=a;
	count++;
	k++;
}
int validityA()
{
if(strlen(vehicleno==10))
{
	for(i=0;i<2;i++)
	{	if('A'<=vehicleno[i] && vehicleno[i]<='Z')
			flag=0;
		else flag=1;
	}
	if(flag==0)
	{	
		for(i=2;i<4;i++)
		{
			if('0'<=vehicleno[i] && vehicleno[i]<='9')
				flag=0;
			else flag=1;
		}
		if(flag==0)
		{
			for(i=4;i<6;i++)
			{
				if('A'<=vehicleno[i] && vehicleno[i]<='Z')
					flag=0;
				else flag=1;
			}
			if(flag==0)
			{	
				for(i=6;i<10;i++)
				{
					if('0'<=vehicleno[i] && vehicleno[i]<='9')
						flag=0;
				}
				if(flag==0)
					 return 1;
				else
					 return 0;
			}
			else
				 return 0;
		}
		else
			 return 0;
		
	}
	else
		 return 0;
	
		
}
else
	 return 0;
}