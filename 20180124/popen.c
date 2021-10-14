#include"func.h"

int main(int argc,char **argv){
		if(argc!=2){
			printf("argc error\n");
			return -1;
		}
	FILE *fp=NULL;
	fp=popen(argv[1],"r");
	if(fp==NULL){
			perror("popen");
			return -1;
	}
	char buf[128]={0};
	int fr_size=fread(buf,sizeof(char),sizeof(buf),fp);
	puts(buf);



}
