#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int find_argv(char*path,char*argv){

	DIR*dir;
		dir=opendir(path);
	if(dir==NULL){
	printf("opendir wrong\n");
	return -1;
	}
			
	struct dirent *p=NULL;
	char buf[512]={0};

	while((p=readdir(dir))!=NULL){
	if(strcmp(p->d_name,".")==0||strcmp(p->d_name,"..")==0){}
	else{
			
		if(strcmp(p->d_name,argv)==0){
			puts(getcwd(NULL,0));
			exit(0);
			}
		if(p->d_type==4){
		sprintf(buf,"%s%s%s",path,"/",p->d_name);
		find_argv(buf,argv);		
			}	
	}	
	}	//	while
	closedir(dir);
	printf("no such file\n");
}



int main(int agrc,char**argv){
	char*path=argv[1];
	if(agrc!=3){
			printf("argc error\n");
			return -1;
	}
	find_argv(path,argv[2]);
			return 0;
}
