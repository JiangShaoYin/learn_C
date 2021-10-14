#include"func.h"

void nonblock(int fd){
	int status=fcntl(fd,F_GETFL);
	status=status|O_NONBLOCK;
	fcntl(fd,F_SETFL,status);

}

int main(){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
			ser.sin_family=AF_INET;
			ser.sin_port=htons(1990);
			printf("ser.sin_port=%d\n",ser.sin_port);
			ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	int reuse=1;

	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));		
		
		
		
	int bind1=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
		
		if(bind1==-1) printf("bind error\n");
	listen(sfd,10);

	struct sockaddr_in client={0};
		int len=sizeof(client);

	//int new_fd=accept(sfd,(struct sockaddr*)&client,&len);
	//		printf("new_fd=%d\n",new_fd);
			
	int epfd=epoll_create(1);
	
	struct epoll_event event,evt[3];
			event.events=EPOLLIN;
			event.data.fd=0;
		epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
			event.data.fd=sfd;
		epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);

	char buf[5]={0};
	int new_fd;
	while(1){
		bzero(evt,sizeof(evt));	
	int ret=epoll_wait(epfd,evt,3,-1);
		if(ret>0){
//		printf("line 42:ret=%d\n",ret);

		for(int i=0;i<ret;i++){
			if(evt[i].data.fd==sfd){		
				new_fd=accept(sfd,(struct sockaddr*)&client,&len);
					printf("new_fd=%d\n",new_fd);
					nonblock(new_fd);
					event.events=EPOLLIN|EPOLLET;
					event.data.fd=new_fd;
				epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
			}
			if(evt[i].data.fd==new_fd){
			while(1){		
				bzero(buf,sizeof(buf));
				int ret_r=recv(new_fd,buf,sizeof(buf)-1,0);
				if(ret_r>0)
					printf("%s",buf);
				if(ret_r==0){
					printf("bye\n");
						close(new_fd);
						epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
						break;
				}if(ret_r==-1){
					break;	
				}
			}
			printf("\n");
			}
			if(evt[i].data.fd==0){
				bzero(buf,sizeof(buf));
				int ret_read=read(0,buf,sizeof(buf));
				if(buf[ret_read-1]='\n')
					send(new_fd,buf,strlen(buf)-1,0);
				else
					send(new_fd,buf,strlen(buf),0);
				if(ret_read==0){
					close(new_fd);
					goto end;			
					}
				}
			}
		}
	}
end:
	close(sfd);
	return 0;
}
