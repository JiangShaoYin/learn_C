#include "func.h"

#define err_exit(m) \
	do\
	{  \
		perror(m); \
		exit(EXIT_FAILURE);  \
	}while(0)

typedef std::vector<struct epoll_event> EventList;

int setUnBlock(int fd)
{
	int flags=fcntl(fd,F_GETFL);
	if(flags==-1)
		exit(-1);

		flags|=O_NONBLOCK;
	if(fcntl(fd,F_SETFL,flags)==-1)
		exit(-1);
	return 0;
}


ssize_t readn(int fd,void *buf,size_t count)
{
	size_t nleft = count;
	ssize_t nread=0 ;
	char *pbuf=(char*)buf;
	
	while(nleft>0)
	{
		nread=read(fd,pbuf,nleft);
		if(nread<0)
		{
			if(errno==EINTR)	
				continue;
		    else
				return -1;
			
		}else if(nread==0)
		      return count-nleft;
		
		nleft-=nread;
		pbuf+=nread;
	}

	return count;
}

ssize_t writen(int fd, const void *buf, size_t count)
{
	
	size_t nleft = count;
	ssize_t nwrite=0 ;
	char *pbuf=(char*)buf;
	
	while(nleft>0)
	{
		nwrite=write(fd,pbuf,nleft);
		if(nwrite<0)
		{
			if(errno == EINTR)
				continue;
			else
				return -1;
			
		}else if(nwrite==0)
			continue;
		
		nleft-=nwrite;
		pbuf+=nwrite;
	}

	return count;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
	while(1)
	{
		int ret=recv(sockfd,buf,len,MSG_PEEK);
		if(ret==-1 && errno==EINTR)
			continue;
		return ret;
	}
}

ssize_t readline(int sockfd, void *buf, size_t maxline)
{
	int ret;
	int nread;
	char *bufp=static_cast<char*>(buf);
	int nleft = maxline;

	while(1)
	{
		ret=recv_peek(sockfd,bufp,nleft);
		if(ret<0)
			return ret;
		else if(ret ==0)
			return ret;
		nread=ret;
		int i=0;
		for(i=0;i<nread;i++)
		{
			if(bufp[i]=='\n')
			{
				ret=readn(sockfd,bufp,i+1);
				if(ret!=i+1)
					exit(-1);
				return ret;
			}
		}
		if(nread>nleft)
			exit(-1);
		nleft-=nread;
		ret=readn(sockfd,bufp,nread);
		if(ret!=nread)
			exit(-1);
		bufp+=nread;
	}
	return -1;

}


void handler_signal(int sig)
{
	while(waitpid(-1,NULL,WNOHANG)>0)
		;
}


int main(void)
{
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1)
		err_exit("sockset");

	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(9000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	int on=1;
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
		err_exit("setsockopt");

	if(bind(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
		err_exit("bind");

	if(listen(sock,SOMAXCONN)==-1)
		err_exit("listen");
	
	std::vector<int> clients;
	int conn;
	int nready;
	EventList events(16);
	int epollfd;
	struct epoll_event event;
	char buf[512];

	struct sockaddr_in peeraddr;
	socklen_t peerlen;

	epollfd=epoll_create1(EPOLL_CLOEXEC);	
	event.events=EPOLLIN|EPOLLET;
	event.data.fd=sock;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,sock,&event);

	while(1)
	{
		nready =epoll_wait(epollfd,&*events.begin(),static_cast<int>(events.size()),-1);

	puts("\nepoll_wait done");	
	printf("nready=%d\n",nready);
		for(int j=0;j<nready;j++)
			printf("events[%d].data.fd=%d\n",j,events[j].data.fd);

		printf("%d,%d\n",nready,events[0].data.fd);
		for(int i=0;i<nready;i++)
		{
			if(events[i].data.fd==sock)
			{
				printf("zuse 1\n");
				peerlen=sizeof(peeraddr);
				conn=accept(sock,(struct sockaddr*)&peeraddr,&peerlen);
				if(conn==-1)
						err_exit("accept");
				printf("ip=%s,port=%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
				event.data.fd==conn;
				event.events=EPOLLIN|EPOLLET;
				
				int ret=epoll_ctl(epollfd,EPOLL_CTL_ADD,conn,&event);
				if(ret==-1)
					err_exit("epoll_ctl");
				printf("conn=%d\n",conn);
			}
			else if(events[i].events & EPOLLIN)
			{
				    conn=events[i].data.fd;
					bzero(buf,sizeof(buf));
					printf("zuse 2\n");
					int ret=readline(conn,buf,512);
					if(ret>0)
					{
						fputs(buf,stdout);
						writen(conn,buf,strlen(buf));
					}
					else if(ret==-1)
						err_exit("readline");
					else
					{
						printf("client close\n");
						close(conn);

						event=events[i];
						epoll_ctl(epollfd,EPOLL_CTL_DEL,conn,&event);
					}
				}
			
			}
	  }	
		return 0;
}
