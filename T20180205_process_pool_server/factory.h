#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef  void* (*pfunc)(void*);

typedef struct{
	que_t que;
	pthread_cond_t cond;	
	pthread_t* pthid;		//线程id 
	int flag;
	pfunc thread_func;		//线程处理函数 
	int thread_num;
}factory,*pfac;

void factory_init(pfac p,int thread_num,int capacity,pfunc tran_file);
void factory_start(pfac);
int sendn(int,char*,int);
void trans_file(int);
#endif
