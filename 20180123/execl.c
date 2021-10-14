#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
	execl("./add","new process","2","3",NULL);
	while(1);
	return 0;



}
