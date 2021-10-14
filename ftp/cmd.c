#include"func.h"

int cmd(int new_fd){
//		printf("服务器子进程准备接收命令：\n");
		train t={0};
		int i,j;//for循环里面用的变量
		char mingling[3]={0};
		char canshu[100]={0};
		char *mycmd[]={"cd","ls","put","get","del","pwd","exit",NULL};

		int ret=recv(new_fd,(char*)&t.len,sizeof(t.len),0);//接收长度
				recv(new_fd,(char*)&t.flag,sizeof(t.flag),0);
				recv(new_fd,t.buf,t.len-1,0);
		if(0==ret||ret<0){//send端掉线，rec返回0；
			perror("recv");
			return -1;		
			}
//		int ret=recvn(new_fd,t.buf,sizeof(t.buf));用循环发送时，发送和接收的大小必须一致，如果发送3，接收1000，则接收方阻塞在recv
//			printf("ret=%d\n",ret);
		printf("cmd received\n");
		printf("%s\n",t.buf);
		for(i=0;t.buf[i]!=' '&&t.buf[i]!=0;i++)
				mingling[i]=t.buf[i];
		int pos=i+1;
		for(j=0;t.buf[pos+j]!=0;j++)
				canshu[j]=t.buf[pos+j];
		int cmdnum=-1;
		for(int i=0;mycmd[i]!=NULL;i++){
			if(strcmp(mingling,mycmd[i])==0){
					cmdnum=i;
					break;
			}
		}
		switch(cmdnum){
			case 0:CD(new_fd,canshu);break;
			case 1:LS(new_fd);break;
			case 2:jieshou(new_fd);break;
			case 3:trans_file(new_fd,canshu);break;
			case 4:DEL(new_fd,canshu);break;
			case 5:PWD(new_fd);break;
			case 6:break;
			case 7:break;
		}
		return 0;
	}

int CD(int new_fd,char *canshu){
	char *path=NULL;
		chdir(canshu);//危险操作，非法访问
		path=getcwd(NULL,0);
	if(strcmp(path,ROOTDIR)<0||strcmp(path,ROOTDIR)==0)//path小于等于rootdir，说明越界了
		canshu=ROOTDIR;	
	chdir(canshu);
	LS(new_fd);
	return 0;
}

int LS(int new_fd){
	char *path=NULL;
	train t={0};
//	char buf[128]={0};
	path=getcwd(NULL,0);
	DIR*dir=opendir(path);//open返回指向DIR结构体的指针，该指针可被几个与目录有关的函数（readdir，）使用，返回目录的相关信息
	struct dirent*dinfo=NULL;//dirent结构体代表了，由dir指向的目录流中的下一个目录项，保存着目录项的相关信息(相对于目录起始位置的偏移，文件类型，文件名等)，想得到文件的具体信息，用stat函数获取
	struct stat filestat;//filestat结构体返回文件详细信息
		while((dinfo=readdir(dir))!=NULL){//readdir迭代读取目录
			if(strcmp(dinfo->d_name,".")==0||strcmp(dinfo->d_name,"..")==0){}
			else{
				stat(dinfo->d_name,&filestat);
				if(dinfo->d_type==8)
				sprintf(t.buf,"%-25s%ldB",dinfo->d_name,filestat.st_size);
				else if(dinfo->d_type==4)
				sprintf(t.buf,"%s/",dinfo->d_name);

				t.len=strlen(t.buf);
				t.flag=1;
				puts(t.buf);
					sendn(new_fd,(char*)&t,8+t.len);
				}
		}
					//close(new_fd);
		//write(new_fd,&c,sizeof(c));
	return 0;
}

				//	send(new_fd,dinfo,sizeof(struct dirent),0);

void sig(int signum){
	printf("sigpipe is coming\n");
}

int trans_file(int new_fd,char *canshu){
	printf("%s--------\n",canshu);
	train t;
	strcpy(t.buf,canshu);
	t.len=strlen(t.buf);
	t.flag=2;
		sendn(new_fd,(char*)&t,8+t.len);
	int fd=open(canshu,O_RDONLY);

	while(bzero(&t,sizeof(t)),t.flag=2,(t.len=read(fd,t.buf,sizeof(t.buf)))>0){
		int ret=sendn(new_fd,(char*)&t,8+t.len);
		if(ret==-1){
		goto end;
		}	
	}
	t.len=0;				//可以不加这句话，因为最后一次read返回0
	sendn(new_fd,(char*)&t,4);//高危处
end:
	close(fd);				//如果client掉线，server子进程关闭传文件的描述符，return 0，此时子程序在一直等待接收client的命令，
							//由于client掉线，所以server子进程的cmd函数中recv返回-1，此时子进程发现客户断掉，退出接收client命令
	//close(new_fd);		//的循环，给父进程管道里写个消息，开始睡眠。
		char c='c';
		//write(new_fd,&c,sizeof(c));
	return 0;
}

int jieshou(int sfd){
	train t;
	bzero(&t,sizeof(t));
		recvn(sfd,(char*)&t.len,sizeof(t.len));//接收文件名
		recvn(sfd,(char*)&t.flag,sizeof(t.flag));
		recvn(sfd,t.buf,t.len);
	int fd;
	printf("-------------------------------");
	printf("t.len=%d\n",t.len);
	printf("t.flag=%d\n",t.flag);
	printf("t.buf=%s\n",t.buf);
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
				printf("t.len=%d",t.len);
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

int DEL(int new_fd,char *canshu){
	remove(canshu);
	LS(new_fd);
 	return 0;
}

int PWD(int new_fd){
	char *path=NULL;
	path=getcwd(NULL,0);
	puts(path);
}