#include"func.h"
typedef struct{
	int i;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}rail;

void *func1(void*r){
	rail*p=(rail*)r;
	int count=0;
while(1){	
	pthread_mutex_lock(&p->mutex);
		if(p->i>0){			
			printf("sale 1 total tickets:%d\n",p->i);
			p->i--;
			count++;
			printf("sale 1 after sale tickets:%d\n",p->i);
			if(p->i==0){
				pthread_cond_signal(&p->cond);//���ȴ�cond���̷߳����ź�.
			}
			pthread_mutex_unlock(&p->mutex);
			sleep(1);
		}
		else{
			pthread_mutex_unlock(&p->mutex);
			printf("sale1 has sold:%dtickets\n",count);
			break;
		}
	}
}

void *func2(void*r){
	rail*p=(rail*)r;
	int count=0;
while(1){	
	pthread_mutex_lock(&p->mutex);
		if(p->i>0){			
			printf("sale 2  total tickets:%d\n",p->i);
			p->i--;
			count++;
			printf("sale 2  after sale tickets:%d\n",p->i);
			if(p->i==0){
				pthread_cond_signal(&p->cond);
			}
			pthread_mutex_unlock(&p->mutex);
			sleep(1);
		}
		else{
			pthread_mutex_unlock(&p->mutex);
			printf("sale 2 has sold:%dtickets\n",count);
			break;
		}
	}
}

int main(){
	rail r;
	pthread_t thread1,thread2;
	pthread_mutex_init(&r.mutex,NULL);//��ʼ����ͨ��
			pthread_cond_init(&r.cond,NULL);//��ʼ����������r.cond
	r.i=20;							//��Դ������
	pthread_create(&thread1,NULL,func1,&r);	//������Ʊ�߳�thread1���߳���ں���func1
	pthread_create(&thread2,NULL,func2,&r);
		pthread_mutex_lock(&r.mutex);//Ҫ���ʱ���i������Ҫ������
		if(r.i>0){
			pthread_cond_wait(&r.cond,&r.mutex);//r.i>0�����̱߳������ڵȴ�cond�Ķ����ϣ���signal���Ѻ󣬵�һ��Ӧ�Ǽ�����Ȼ������������ߡ�
		}
		r.i=20;
		printf("add tickets 20\n");
		pthread_mutex_unlock(&r.mutex);
	pthread_join(thread1,NULL);//�����߳�thread1����Դ
	pthread_join(thread2,NULL);
	return 0;
}
