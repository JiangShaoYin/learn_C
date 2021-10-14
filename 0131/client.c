#include"func.h"

int main(){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
		ser.sin_family=AF_INET;
		ser.sin_port=htons(1990);
		ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	
//	bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
//	listen(sfd,10);
//	struct sockaddr_in client={0};
//		int len=sizeof(client);
//	int new_fd=accept(sfd,(struct sockaddr*)&client,&len);


	fd_set fdset;
	char buf[128]={0};
	while(1){
		FD_ZERO(&fdset);
		FD_SET(0,&fdset);
		FD_SET(sfd,&fdset);
	int ret=select(sfd+1,&fdset,NULL,NULL,NULL);
	if(ret>0){
		if(FD_ISSET(0,&fdset)){
			bzero(buf,sizeof(buf));
			read(0,buf,sizeof(buf));
			int ret_s=send(sfd,buf,sizeof(buf),0);
				if(ret_s==0)
					break;			
				}
		if(FD_ISSET(sfd,&fdset)){
			bzero(buf,sizeof(buf));
			int ret_r=recv(sfd,buf,sizeof(buf),0);
			printf("%s",buf);
			if(ret_r==0)
					break;
			}
		}
	}
	close(sfd);
	return 0;
}
