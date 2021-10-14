#include "func.h"
	train t={0};

int main(){
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser={0};
			ser.sin_family=AF_INET;
			ser.sin_port=htons(1990);
			ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret){
		perror("connect");
		return -1;
	}
	int epfd=epoll_create(1);
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(2,sizeof(struct epoll_event));
		event.data.fd=sfd;
		event.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);	
		event.data.fd=0;
	epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);	
	while(1){
		int nrecv=epoll_wait(epfd,evs,2,-1);
		for(int i=0;i<nrecv;i++){
			if(0==evs[i].data.fd){
				bzero(&t,sizeof(t));
					ret=read(0,t.buf,sizeof(t.buf));
					t.len=strlen(t.buf);//发送小火车（命令+命令长度）
//			printf("t.buf=%s\n",t.buf);
					ret=send(sfd,&t,8+t.len-1,0);
				char buf[4]={0};
				memcpy(buf,t.buf,3);
					if(strcmp(buf,"put")==0){
						char filename[100]={0};
						memcpy(filename,t.buf+4,strlen(t.buf)-5);//t.buf的前4个字符为put+空格 
						trans_file(sfd,filename);
					}
				}
			if(sfd==evs[i].data.fd){
					bzero(&t,sizeof(t));
					recvn(sfd,(char*)&t.len,sizeof(t.len));//接收文件名
					recvn(sfd,(char*)&t.flag,sizeof(t.flag));
//printf("t.flag=%d\n",t.flag);
					if(t.flag==1)
							show(sfd);
					else if(t.flag==2)
							jieshou(sfd);
			}
		}
	}
	printf("close sfd done\n");	
	close(sfd);
}			
