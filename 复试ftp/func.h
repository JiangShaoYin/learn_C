#include<errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <strings.h>
#include <time.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/epoll.h>
#include <dirent.h>
#define ROOTDIR "/home/jiang/ftp"

typedef struct{
	pid_t pid;
	int pfd;//子进程管道的对端
	short busy;//标识进程是否忙碌
}data,*pdata;

typedef struct{
	int len;
	int flag;//flag=1表示传递的是显示信息，flag=2表示传递文件
	char buf[1000];
}train;

//#define FILENAME "file"
void make_child(pdata p,int pro_num);
void child_handle(int pfd);
void sent_fd(int,int,short);
void recv_fd(int,int*,short*);
int trans_file(int,char*);
int sendn(int,char*,int);
int recvn(int sfd,char* buf,int len);
int cmd(int new_fd);
int CD(int,char *);
int LS(int);
int DEL(int,char *canshu);
int PWD(int new_fd);
int jieshou(int sfd);
int UPLOAD(int new_fd);
void sig(int);
