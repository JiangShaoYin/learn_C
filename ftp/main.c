#include"func.h"
int fds[2];

void sig_exit(int signum){
	char c='a';
	write(fds[1],&c,sizeof(c));	

}

int main(){
	int pro_num=2;
	pdata p=(pdata)calloc(pro_num,sizeof(data));
	make_child(p,pro_num);
	int sfd=socket(AF_INET,SOCK_STREAM,0);//生成套接口描述符
//		printf("sfd=%d\n",sfd);
	int reuse=1;//设置sfd属性为reuse，这样当客户端断开后，端口不必等待（否则要等待tcp4次挥手完成后，这个socket描述符才可以重新使用）
	int ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));//设置socket选项，（&resue是指针，指向存放选项值的缓冲区，缓冲区大小为sizeof（int））
		struct sockaddr_in ser={0};//用一个套接字地址结构体，将服务器的ip地址和端口号等信息填入
			ser.sin_family=AF_INET;
			ser.sin_port=htons(1990);
			ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));//（将套接口与指定的端口号和ip地址相连）
	int epfd=epoll_create(1);//创建epoll句柄
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(pro_num,sizeof(struct epoll_event));//创建epoll_event结构体，将要监控的描述符和监控的事件填入
		event.data.fd=sfd;
		event.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);//向内核，注册要监控的事件
	for(int i=0;i<pro_num;i++){
		event.data.fd=p[i].pfd;
		event.events=EPOLLIN;
			epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].pfd,&event);
		}
	
	pipe(fds);
		event.events=EPOLLIN;
		event.data.fd=fds[0];
		epoll_ctl(epfd,EPOLL_CTL_ADD,fds[0],&event);
	signal(SIGUSR1,sig_exit);

	listen(sfd,pro_num);
	char flag;//把fds[0]字符读掉
	int j;
	while(1){
		int nrecv=epoll_wait(epfd,evs,pro_num+2,-1);
		for(int i=0;i<nrecv;i++){
			if(fds[0]==evs[i].data.fd){
				printf("father want exit\n");
					read(fds[0],&flag,sizeof(flag));
						event.events=EPOLLIN;
						event.data.fd=sfd;
						epoll_ctl(epfd,EPOLL_CTL_DEL,sfd,&event);
					for(j=0;j<pro_num;j++){
						sent_fd(p[j].pfd,0,1);//flag=1表示，父进程告诉子进程自己要退出，随便发个文件
						}					//描述符过去（本例是0），主要是利用sendmsg发送结束标识flag
					for(j=0;j<pro_num;j++){
						wait(NULL);		//回收子进程资源			
					}
					exit(0);
				}
			if(sfd==evs[i].data.fd){
				int new_fd=accept(sfd,NULL,NULL);
					for( j=0;j<pro_num;j++){
						if(0==p[j].busy){
							break;
						}
					}
				sent_fd(p[j].pfd,new_fd,0);
				p[j].busy=1;
				printf("%d child is busy\n",p[j].pid);
				close(new_fd);
			}
			for(j=0;j<pro_num;j++){   //判断与父进程相连的哪一个管道里面有消息（子进程通知父进程，我闲了）
				if(evs[i].data.fd==p[j].pfd){
					read(p[j].pfd,&flag,sizeof(flag));
					p[j].busy=0;
					printf("%d child is not busy\n",p[j].pid);
			//		return -1;
				}
			
			}
		}
	}
}
