#include "func.h"

int main(){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser={0};
			ser.sin_family=AF_INET;
			ser.sin_port=htons(1990);
			ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	char buf[1000]={0};
	int len;
	int time1,time2;
	time1=time(NULL);
	recvn(sfd,(char*)&len,sizeof(len));//接收文件名
	recvn(sfd,buf,len);
	int fd;
	fd=open(buf,O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		recvn(sfd,(char*)&len,sizeof(len));
		if(len>0)
		{
			bzero(buf,sizeof(buf));
			recvn(sfd,buf,len);
			write(fd,buf,len);
		}else{
			break;
		}
	}
	time2=time(NULL);
	printf("%ds\n",time2-time1);
	close(fd);
	close(sfd);
}

