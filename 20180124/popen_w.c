#include"func.h"

int main(int argc,char **argv){
		if(argc!=2){
			printf("argc error\n");
			return -1;
		}
	FILE *fp=NULL;
	fp=popen(argv[1],"w");
		char buf[128]="3 4\n";
	if(fp==NULL){
			perror("popen");
			return -1;
	}
	int fr_size=fwrite(buf,sizeof(char),strlen(buf),fp);
	sleep(3);
//	pclose(fp);

	printf("father\n");


}
