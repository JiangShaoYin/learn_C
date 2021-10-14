#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

int main(int argc,char**argv){
	struct dirent *pdirinfo;
	DIR *pdir;
	pdir=opendir(argv[1]);//pdir是指向文件夹的指针
	long pos1=telldir(pdir);
		pdirinfo=readdir(pdir);
		printf("文件夹名字为:%s\n",pdirinfo->d_name);
	long pos2=telldir(pdir);
	seekdir(pdir,pos2);
	






}
