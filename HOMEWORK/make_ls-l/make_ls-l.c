#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int JudgeArgs(int, int);

char* ChangeMode(unsigned short num)
{
	char mode[4]={'x','w','r','-'};
	char *buf=(char*)calloc(10,sizeof(char));
	int md=0;
	for(int i=0;i<9;i++)
	{	
		md=i%3;
		if(num%2)
			buf[9-i]=mode[md];			
		else
			buf[9-i]='-';
		num/=2;
	}
	for(int i=0;i<5;i++) num/=2;
	if(	num%2)
		buf[0]='d';
	else
		buf[0]='-';
	return buf;
}

int main(int args,char *argv[])
{
	if(JudgeArgs(args,1)==-1)
		return -1;

	char *pathname=argv[1];	
	
	DIR *dir = opendir(pathname);
	if(dir==NULL)
	{	
		perror("dir");
		return -1;	
	}

	struct stat fileStat;
	memset(&fileStat, 0 ,sizeof(fileStat));
	int ret=0;
	struct dirent *dirInfor;
	char *fileName={0};
	while(dirInfor=readdir(dir))
	{
		fileName=dirInfor->d_name;
		ret=stat(fileName,&fileStat);
		if(-1==ret)
		{
			perror("stat");
			return -1;
		}
		printf("%ld %s %ld %s %s %ld %s %s\n",fileStat.st_ino,ChangeMode(fileStat.st_mode),fileStat.st_nlink,getpwuid(fileStat.st_uid)->pw_name,getgrgid(fileStat.st_gid)->gr_name,fileStat.st_size,ctime(&fileStat.st_mtime),fileName);		
	}
	closedir(dir);
	return 0;
	

}
