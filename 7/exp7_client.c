/*************************************************************************
	> File Name: exp7_client.c
	> Author: 计科三班2013301500100秦贤康
	> Mail: qinxiankang@gmail.com
	> Created Time: 2015年12月05日 星期六 22时41分00秒
 ************************************************************************/

/*
请编写一个简单的基于TCP的服务器、客户端模拟系统。该模拟系统中服务器端一直监听本机的6666号端口，如果收到连接请求，将接收请求并接收客户端发来的消息；客户端与服务器端建立连接并发送一条消息。*/


/* 客户端 */

#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/msg.h>  
#include <errno.h>  
  
#define MAX_TEXT 512  
struct msg_st  
{  
    long int msg_type;  
    char text[MAX_TEXT];  
};  
  
int main()  
{  
    int running = 1;  
    struct msg_st data;  
    char buffer[BUFSIZ];  
    int msgid = -1;  
  
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
  
    //向消息队列中写消息，直到写入end  
    while(running)  
    {  
        //输入数据  
        printf("Enter some text: ");  
        fgets(buffer, BUFSIZ, stdin);  
        data.msg_type = 1;    //注意2  
        strcpy(data.text, buffer);  
        //向队列发送数据  
        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)  
        {  
            fprintf(stderr, "msgsnd failed\n");  
            exit(EXIT_FAILURE);  
        }  
        //输入end结束输入  
        if(strncmp(buffer, "end", 3) == 0)  
            running = 0;  
        sleep(1);  
    }  
    exit(EXIT_SUCCESS);  
}  

