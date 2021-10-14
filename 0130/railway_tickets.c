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
				pthread_cond_signal(&p->cond);//给等待cond的线程发送信号.
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
	pthread_mutex_init(&r.mutex,NULL);//初始化普通锁
			pthread_cond_init(&r.cond,NULL);//初始化条件变量r.cond
	r.i=20;							//资源的数量
	pthread_create(&thread1,NULL,func1,&r);	//创建卖票线程thread1，线程入口函数func1
	pthread_create(&thread2,NULL,func2,&r);
		pthread_mutex_lock(&r.mutex);//要访问变量i，所以要加锁。
		if(r.i>0){
			pthread_cond_wait(&r.cond,&r.mutex);//r.i>0所以线程被阻塞在等待cond的队列上，被signal唤醒后，第一反应是加锁，然后程序再往下走。
		}
		r.i=20;
		printf("add tickets 20\n");
		pthread_mutex_unlock(&r.mutex);
	pthread_join(thread1,NULL);//回收线程thread1的资源
	pthread_join(thread2,NULL);
	return 0;
}
