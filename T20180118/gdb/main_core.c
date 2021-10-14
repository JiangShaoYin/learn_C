#include <string.h>
#include <stdio.h>

void print(int i)
{
	printf("print i=%d\n",i);
	i=5;
	char *p=NULL;//制造程序崩溃
	strcpy(p,"hello");	
	printf("modify print i=%d\n",i);
}

int main()
{
	int j=10;
	int a[5]={1,2,3,4,5};
	print(j);
	printf("j=%d\n",j);
	for(j=0;j<10;j++)
	{
		printf("j=%d\n",j);
	}
	return 0;
}
