/*************************************************************************
	> File Name: exp7_server.c
	> Author: 计科三班2013301500100秦贤康
	> Mail: qinxiankang@gmail.com
	> Created Time: 2015年12月05日 星期六 22时34分44秒
 ************************************************************************/

/*
请编写一个简单的基于TCP的服务器、客户端模拟系统。该模拟系统中服务器端一直监听本机的6666号端口，如果收到连接请求，将接收请求并接收客户端发来的消息；客户端与服务器端建立连接并发送一条消息。*/


/* 服务器 */

#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/msg.h> 

  
struct msg_st  
{  
    long int msg_type;  
    char text[BUFSIZ];  
};  
  
int main()  
{  
    int running = 1;  
    int msgid = -1;  
    struct msg_st data;  
    long int msgtype = 0; //注意1  
  
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
    //从队列中获取消息，直到遇到end消息为止  
    while(running)  
    {  
        if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1)  
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE);  
        }  
        printf("You wrote: %s\n",data.text);  
        //遇到end结束  
        if(strncmp(data.text, "end", 3) == 0)  
            running = 0;  
    }  
    //删除消息队列  
    if(msgctl(msgid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);   
    }  
    exit(EXIT_SUCCESS);  
}  


