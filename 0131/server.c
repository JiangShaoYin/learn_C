#include"func.h"

int main(){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
		ser.sin_family=AF_INET;
		ser.sin_port=htons(1990);
		printf("ser.sin_port=%d\n",ser.sin_port);
		ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	int bind1=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
		if(bind1==-1) printf("bind error\n");
	listen(sfd,10);
	struct sockaddr_in client={0};
		int len=sizeof(client);
	int new_fd=accept(sfd,(struct sockaddr*)&client,&len);
			printf("new_fd=%d\n",new_fd);
	fd_set fdset;
	char buf[128]={0};
	while(1){
		FD_ZERO(&fdset);
		FD_SET(0,&fdset);
		FD_SET(new_fd,&fdset);
		int ret=select(new_fd+1,&fdset,NULL,NULL,NULL);
		if(ret>0){
			if(FD_ISSET(0,&fdset)){
				bzero(buf,sizeof(buf));
				read(0,buf,sizeof(buf));
				int ret_s=send(new_fd,buf,strlen(buf),0);
				if(ret_s==0)
						break;			
					}
			if(FD_ISSET(new_fd,&fdset)){
				bzero(buf,sizeof(buf));
				int ret_r=recv(new_fd,buf,sizeof(buf),0);
				if(ret_r>0)
					printf("ret_r=%d,%s",ret_r,buf);
				if(ret_r==0)
						break;
				}
			}
		}
	close(new_fd);
	close(sfd);
	return 0;
}
