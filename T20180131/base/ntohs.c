#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	short port;
	port=atoi(argv[1]);
	printf("port=%x\n",port);
	short sin_port;//网络字节序
	sin_port=htons(port);
	printf("sin_port=%x\n",sin_port);
	port=0;
	port=ntohs(sin_port);
	printf("port=%x\n",port);
	return 0;

}
