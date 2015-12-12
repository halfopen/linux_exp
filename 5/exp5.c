/*************************************************************************
	> File Name: exp5.c
	> Author: 计科三班2013301500100秦贤康
	> Mail: qinxiankang@gmail.com
	> Created Time: 2015年12月05日 星期六 22时25分39秒
 ************************************************************************/

/* 编写程序，实现对于二进制信号量的等待和通知操作。*/


#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int number=0; // 被保护的全局变量
sem_t sem_id, sem_pv;
void* Comsumer(void *arg)
{          
        printf("Comsumer wait number:%d\n",number);
        sem_wait(&sem_id);      // v
        //sem_wait(&sem_pv);
        printf("Comsumer end number:%d\n",--number);
        
       // sem_post(&sem_pv);
}
void* Producer(void *arg)
{
        
        printf("\tProducer wait number:%d\n",number);
        sem_post(&sem_id);      //  p
        //sem_wait(&sem_pv);
        printf("\tProducer end number:%d\n",++number);
        //sem_post(&sem_pv);
}
int main(int argc,char *argv[])
{
        number = 0;
        pthread_t id1, id2, id3, id4, id5;
        sem_init(&sem_id, 0, 0);
        sem_init(&sem_pv, 0, 1);
        pthread_create(&id1,NULL,Comsumer, NULL);
        pthread_create(&id2,NULL,Producer, NULL);
        pthread_create(&id3,NULL,Comsumer, NULL);
        pthread_create(&id4,NULL,Producer, NULL);
        
        //pthread_create(&id5,NULL,Comsumer, NULL);
        
        
        pthread_join(id1,NULL);
        pthread_join(id2,NULL);
        pthread_join(id3,NULL);
        pthread_join(id4,NULL);
        
       // pthread_join(id5,NULL);
        printf("main exit number:%d\n",number);  //如果最后number为0,则正确
        return 0;
}
