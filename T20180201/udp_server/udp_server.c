#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));//端口处于激活状态
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int len=sizeof(client);
	char buf[128]={0};
	ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
	if(-1==ret)
	{
		perror("recvfrom");
		return -1;
	}
	printf("buf=%s\n",buf);
	printf("udp_client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	char *p="I am udp server";
	ret=sendto(sfd,p,strlen(p),0,(struct sockaddr*)&client,sizeof(client));
	if(-1==ret)
	{
		perror("sendto");
		return -1;
	}
	close(sfd);
	return 0;
}
