#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>
//B_write
int main(int args,char**argv){
	if(args!=3){
		printf("args error\n");
		return -1;
	}
int fdr=open(argv[1],O_RDONLY);	
	if(fdr==-1){
	perror("open");
	return -1;	
	}
int	fdw=open(argv[2],O_WRONLY);
	if(fdw==-1){
	perror("open");
	return -1;	
	}
printf("i am B:\n");
char buf[128]={0};
	int ret;
	while(1){
        	fd_set rdset;
        	FD_ZERO(&rdset);
        	FD_SET(0,&rdset);
        	FD_SET(fdr,&rdset);
        	ret=select(fdr+1,&rdset,NULL,NULL,NULL);
    	if(ret>0){
			if(FD_ISSET(0,&rdset)){   //输入缓冲区可读，可以写信息到文档
            	memset(buf,0,sizeof(buf));
            	ret=read(0,buf,sizeof(buf));
					if(ret==0){
                    		printf("bye bye");
                    		close(fdr);
                    		close(fdw);
							break;
					}
				write(fdw,buf,strlen(buf)-1);
			}
			if(FD_ISSET(fdr,&rdset)){	
		    	memset(buf,0,sizeof(buf));
         		ret=read(fdr,buf,sizeof(buf));
					if(ret==0){
                     		printf("bye bye");
                     		close(fdr);
                     		close(fdw);
							break;
					}
        		printf("%s\n",buf);
	}}
	}
return 0;
}
