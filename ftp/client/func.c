#include "func.h"
extern train t;

int show(int sfd){
	int ret=recvn(sfd,t.buf,t.len);
//printf("show\n");
//printf("ret=%d",ret);
puts(t.buf);

}



int jieshou(int sfd){
	recvn(sfd,t.buf,t.len);
	int fd;
	fd=open(t.buf,O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		recvn(sfd,(char*)&t.len,sizeof(t.len));
		if(t.len>0)
		{
			bzero(t.buf,sizeof(t.buf));
			recvn(sfd,(char*)&t.flag,sizeof(t.flag));
			recvn(sfd,t.buf,t.len);
			write(fd,t.buf,t.len);
		}else{
			break;
		}
	}
	close(fd);
	return 0;
}
void sig(int signum){
	printf("sigpipe is coming\n");
}



int trans_file(int new_fd,char *canshu){
	printf("%s--------\n",canshu);
	signal(SIGPIPE,sig);
	train t;
	strcpy(t.buf,canshu);
		t.len=strlen(t.buf);
		sendn(new_fd,(char*)&t,8+t.len);
	int fd=open(canshu,O_RDONLY);

	while(bzero(&t,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0){
		int ret=sendn(new_fd,(char*)&t,8+t.len);
		if(ret==-1){
		goto end;
		}	
	}
	t.len=0;				//可以不加这句话，因为最后一次read返回0
	sendn(new_fd,(char*)&t,sizeof(t.len));//高危处
end:
	close(fd);
		char c='c';
	return 0;
}

int sendn(int sfd,char* buf,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=send(sfd,buf+total,len-total,0);
			if(ret==-1){
				printf("客户端掉线\n");
			}
			if(ret==0){
				printf("发送0字节\n");
			}
		total=total+ret;
	}
	return ret;
}


int recvn(int sfd,char* buf,int len)
{
	int total=0;
	int ret;
	while(total<len)
	{
		ret=recv(sfd,buf+total,len-total,0);
		total=total+ret;
	}
	return ret;
}
