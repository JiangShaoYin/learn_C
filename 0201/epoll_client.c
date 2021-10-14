#include"func.h"

int main(){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
			ser.sin_family=AF_INET;
			ser.sin_port=htons(9000);
			printf("ser.sin_port=%d\n",ser.sin_port);
			ser.sin_addr.s_addr=inet_addr("192.168.4.200");
//	int bind1=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));		
//		if(bind1==-1) printf("bind error\n");
//	listen(sfd,10);

	struct sockaddr_in client={0};
		int len=sizeof(client);

//	int new_fd=accept(sfd,(struct sockaddr*)&client,&len);
//			printf("new_fd=%d\n",new_fd);
	connect(sfd,(struct sockaddr*)&ser,sizeof(ser));

	int epfd=epoll_create(1);
	
	struct epoll_event event,evt[2];
			event.events=EPOLLIN;
			event.data.fd=0;
		epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
				event.data.fd=sfd;
		epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);

	char buf[128]={0};
	while(1){
		bzero(evt,sizeof(evt));	
	int ret=epoll_wait(epfd,evt,2,-1);
		if(ret>0){
//		printf("line 35\n");
			for(int i=0;i<ret;i++){
			if(evt[i].data.fd==0){
				bzero(buf,sizeof(buf));
				read(0,buf,sizeof(buf));
				int ret_s=send(sfd,buf,strlen(buf)-1,0);
				if(ret_s==0)
						break;			
					}
			if(evt[i].data.fd==sfd){
//		printf("line 46\n");
				bzero(buf,sizeof(buf));
				int ret_r=recv(sfd,buf,sizeof(buf),0);
//				printf("ret_r=%d\n",ret_r);
				if(ret_r>0)
					printf("%s\n",buf);
				if(ret_r==0)
						break;
				}
			}
		}
	}
	close(sfd);
	close(sfd);
	return 0;
}
