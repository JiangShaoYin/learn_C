#include"func.h"

int main(){
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in ser;
		ser.sin_family=AF_INET;
		ser.sin_port=htons(1990);
		printf("ser.sin_port=%d\n",ser.sin_port);
		ser.sin_addr.s_addr=inet_addr("192.168.4.200");
	int bind1=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
		if(bind1==-1) printf("bind error\n");
	char buf[128]={0};
	struct sockaddr_in client={0};
		int len=sizeof(client);
	printf("line 15\n");
	int ret1=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
	printf("%d\n",ret1);
	printf("%s\n",buf);
	char*p="aaaaaaaaaaaaaa";
	sendto(sfd,p,strlen(p),0,(struct sockaddr*)&client,len);
	
	
	
	
	
	
	close(sfd);
	return 0;
}
