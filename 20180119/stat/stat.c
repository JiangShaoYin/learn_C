 #include <string.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <time.h>
 #include <pwd.h>
 #include <grp.h>

int main(int argc,char *argv[]){
struct stat buf;
memset(&buf,0,sizeof(buf));
int ret=stat(argv[1],&buf);
printf("%x\n",buf.st_mode);



}
