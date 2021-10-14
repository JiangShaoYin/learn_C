#include<stdio.h>

int main(int args,char**agrv){
	FILE*fp=NULL;
	fp=fopen(agrv[1],"rb+");
	char buf[128];
	fseek(fp,5,SEEK_SET);
	long ret=ftell(fp);
	printf("ret=%ld",ret);
	return 0;

}
