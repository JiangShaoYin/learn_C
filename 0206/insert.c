#include<mysql/mysql.h>
#include<stdio.h>
#include<string.h>

int main(){
	char*server="localhost";
	char *user="root";
	char *pwd="123";
	char *database="jiang";
		char query[200]="insert into person(firstname,lastname,age,salary) values('xiong','er',22,5000)";
	puts(query);
	MYSQL *conn=mysql_init(NULL);
	mysql_real_connect(conn,server,user,pwd,database,0,NULL,0);
	mysql_query(conn,query);
    	strcpy(query,"select * from person");
		mysql_query(conn,query);
			MYSQL_RES *res=mysql_use_result(conn);
		MYSQL_ROW row;
		while((row=mysql_fetch_row(res))!=NULL){
			for(int t=0;t<mysql_num_fields(res);t++){
				printf("%8s",row[t]);
			}
			printf("\n");		
			}
		mysql_free_result(res);
		mysql_close(conn);
			return 0;	
}
