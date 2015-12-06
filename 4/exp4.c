/*************************************************************************
	> File Name: exp4.c
	> Author: 计科三班2013301500100秦贤康
	> Mail: qinxiankang@gmail.com 
	> Created Time: 2015年12月05日 星期六 22时14分30秒
 ************************************************************************/

/*
创建一个消息队列，实现下列功能：
1)、消息传送字符“I Like Linux!”
2)、实现消息的发送和接收功能，并且若发送或接收出现错误时，会报错。
3)、在程序完成时，消除消息队列的标识符。
*/

#include <stdio.h>
#include <sys/types.h>
#include <iostream>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <cstring> 
#include <unistd.h> 
using namespace std;  
  
struct msgbuff  
{  
    long mtype;  
    char mtext[100];  
};  
  
int main()  
{  
    int msgid = msgget(IPC_PRIVATE,IPC_CREAT|0777);  
    if(msgid<0)  
    {  
        cout<<"create msg queue failed !"<<endl;  
    }  
      
    int cid = fork();  
    if(cid>0)  
    {  
        msgbuff msg = {1,"I Like Linux!"};  
        msgsnd(msgid,&msg,sizeof(msg),IPC_NOWAIT);  
          
        sleep(2);  
        msgrcv(msgid,&msg,sizeof(msg),1,IPC_NOWAIT);  
        cout<<msg.mtext<<endl;  
    }  
    else if(cid == 0)//子进程先收消息  
    {  
        msgbuff msg;  
        msgrcv(msgid,&msg,sizeof(msg),1,IPC_NOWAIT);  //从消息队列中读取消息
        cout<<msg.mtext<<endl;   
          
        strcpy(msg.mtext,"I Like Linux ,too!");  
        msgsnd(msgid,&msg,sizeof(msg),IPC_NOWAIT);      //将一个新的消息写入队列
    }  
    return 0;  
}  
