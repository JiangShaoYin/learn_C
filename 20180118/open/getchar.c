#include<stdio.h>

int main(){
		char c;
while((c=getchar())!=EOF){
	putchar(c);
}
printf("putchar has done\n");
return 0;
}
