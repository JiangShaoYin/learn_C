#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void FindFile(char *path,char *objFile)
{
	
	char buf[128]={0};
	DIR *dir = opendir(path);
	if(dir==NULL)
	{	
		perror("dir");
		return;	
	}
	struct dirent *dirInfor;
	while(dirInfor=readdir(dir))
	{
		sprintf(buf,"%s%s%s",path,"/",dirInfor->d_name);
		if(dirInfor->d_type==4&&(strcmp(dirInfor->d_name,".")!=0)&&(strcmp(dirInfor->d_name,"..")!=0))
			FindFile(buf,objFile);
		else if(strcmp(dirInfor->d_name,objFile)==0)
		{
			printf("Find the target\n");
			puts(buf);
			break;
		}	
	}
	closedir(dir);
}

int main(int args, char *argv[])
{
	if(args<3)
	{
		perror("args");
		return -1;		
	}
	
	//get current work path directory
	chdir(argv[1]);
	char *workPath=NULL;
	//char buf[128]={0};
	workPath=getcwd(NULL,0);
	//sprintf(buf,"%s%s",workPath,"/");
	FindFile(workPath,argv[2]);	

}
