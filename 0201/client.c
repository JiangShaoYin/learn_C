#include"func.h"

int main(){
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in ser;
		ser.sin_family=AF_INET;
		ser.sin_port=htons(1990);
		printf("ser.sin_port=%d\n",ser.sin_port);
		ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	char buf[128]={0};
	struct sockaddr_in client={0};
		int len=sizeof(client);
	char*p="bbbbbbbbbbbbbbbbbbbbb";
	sendto(sfd,p,strlen(p),0,(struct sockaddr*)&ser,len);
	
	recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
	printf("%s\n",buf);
	
	
	
	
	
	close(sfd);
	return 0;
}
