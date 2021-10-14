#include"func.h"

void make_child(pdata p,int pro_num){
	int fds[2];
	pid_t pid;
	for(int i=0;i<pro_num;i++){
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
//		printf("fds[0]=%d,fds[1]=%d\n\n",fds[0],fds[1]);
		pid=fork();
		if(0==pid){
			close(fds[1]);
			child_handle(fds[0]);
		}
			close(fds[0]);
			p[i].pid=pid;
			p[i].pfd=fds[1];//父进程保存与子进程通信的管道的写端
			p[i].busy=0;
//			printf("	p[%d].pfd=%d\n",i,p[i].pfd);
	}
}

void child_handle(int pfd){
	int new_fd;
	char c;
	short flag=-1;
	while(1){
			recv_fd(pfd,&new_fd,&flag);//接收父进程传给他的pfd
			if(flag==0){
				trans_file(new_fd);
			}
			else
				exit(0);
			write(pfd,&c,sizeof(c));
			}
}

void sig(int signum){
	printf("sigpipe is coming\n");
}

void trans_file(int new_fd){
	signal(SIGPIPE,sig);
	train t;
	strcpy(t.buf,FILENAME);
	t.len=strlen(t.buf);
		sendn(new_fd,(char*)&t,4+t.len);
	int fd=open(FILENAME,O_RDONLY);

	while(bzero(&t,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0){
		int ret=sendn(new_fd,(char*)&t,4+t.len);
		if(ret==-1){
			goto end;
		}	
	}
	t.len=0;				//可以不加这句话，因为最后一次read返回0
	sendn(new_fd,(char*)&t,4);//高危处
								//告诉client发送完毕
end:
	close(fd);
	close(new_fd);
}

int sendn(int new_fd,char*buf,int len){
	int total=0;
	int ret;
	while(total<len){
		ret=send(new_fd,buf+total,len-total,0);
		if(ret==-1){
			printf("客户端下线\n");
			return -1;
		}
			total=total+ret;
	}
	return 0;
}

void sent_fd(int pfd,int fd,short flag){
	struct msghdr msg={0};

	struct iovec iov[2];
//	char buf1[10]="hello";
	char buf2[10]="world";
		iov[0].iov_base=&flag;
		iov[1].iov_base=buf2;
		iov[0].iov_len=2;
		iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;

	struct cmsghdr*cmsg=NULL;
		int len=CMSG_LEN(sizeof(int));
		cmsg=(struct cmsghdr*)calloc(1,len);
			cmsg->cmsg_len=len;	
			cmsg->cmsg_level=SOL_SOCKET;	
			cmsg->cmsg_type=SCM_RIGHTS;
		*(int*)CMSG_DATA(cmsg)=fd;	
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	sendmsg(pfd,&msg,0);
}

void recv_fd(int pfd,int *fd,short *flag){
	struct msghdr msg={0};

	struct iovec iov[2];
//	char buf1[10]="hello";
	char buf2[10]="world";
		iov[0].iov_base=flag;
		iov[1].iov_base=buf2;
		iov[0].iov_len=2;
		iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;

	struct cmsghdr*cmsg=NULL;
		int len=CMSG_LEN(sizeof(int));
		cmsg=(struct cmsghdr*)calloc(1,len);
			cmsg->cmsg_len=len;	
			cmsg->cmsg_level=SOL_SOCKET;	
			cmsg->cmsg_type=SCM_RIGHTS;
		
	msg.msg_control=cmsg;
	msg.msg_controllen=len;

	recvmsg(pfd,&msg,0);
	*fd=*(int *)CMSG_DATA(cmsg);
}
