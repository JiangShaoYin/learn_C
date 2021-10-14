#include<stdio.h>
#include<string.h>

typedef struct stu{
	int num;
	char name[20];
	int score;
}stu; 


int main(){
	stu s={1001,"xiongda",378},tmp;
	char buf[100]={0};
	sprintf(buf,"%d %s %d",s.num,s.name,s.score);
	puts(buf);
	memset(&tmp,0,sizeof(s));
	sscanf(buf,"%d%s%d",&tmp.num,tmp.name,&tmp.score);
	printf("%d %s %d\n",tmp.num,tmp.name,tmp.score);
		return 0;
	
	
}
