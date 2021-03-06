#include "func.h"

typedef struct{
	int tickets;
	pthread_mutex_t mutex;
}Data;

void* salewindow1(void *p)
{
	Data* t=(Data*)p;
	int i=0;
	while(1)
	{
		pthread_mutex_lock(&t->mutex);
		if(t->tickets>0)
		{
		//	printf("I am salewindow1,I will sale %d\n",t->tickets);
			t->tickets--;
			i++;
		//	printf("I am salewindow1,I have saled %d\n",t->tickets);
			pthread_mutex_unlock(&t->mutex);
		}else{
			pthread_mutex_unlock(&t->mutex);
			printf("I am salewindow1,I have saled %d\n",i);
			break;
		}
	}
}

void* salewindow2(void *p)
{
	Data* t=(Data*)p;
	int i=0;
	while(1)
	{
		pthread_mutex_lock(&t->mutex);
		if(t->tickets>0)
		{
		//	printf("I am salewindow2,I will sale %d\n",t->tickets);
			t->tickets--;
			i++;
		//	printf("I am salewindow2,I have saled %d\n",t->tickets);
			pthread_mutex_unlock(&t->mutex);
		}else{
			pthread_mutex_unlock(&t->mutex);
			printf("I am salewindow2,I have saled %d\n",i);
			break;
		}
	}
}

int main()
{
	pthread_t pthid1,pthid2;
	Data t;
	t.tickets=1000000;
	pthread_mutex_init(&t.mutex,NULL);
	
	pthread_create(&pthid1,NULL,salewindow1,&t);
	pthread_create(&pthid2,NULL,salewindow2,&t);
	
	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	return 0;
}
