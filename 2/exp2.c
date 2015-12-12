/*************************************************************************
	> File Name: exp2.c
	> Author: 计科三班2013301500100秦贤康
	> Mail: qinxiankang@gmail.com
	> Created Time: 2015年12月05日 星期六 21时57分37秒
 ************************************************************************/

/*捕捉ctrl+c发送的SIGINT与ctrl+\发送的SIGQUIT信号，并使用sigaction()安装信号。*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//接收ctrl + c 与ctrl+ \信号
void show_handler(int sig)
{
    if( sig == SIGINT){         //如果是ctrl +c 信号
        printf("\nI got signal id=%d, SIGINT\n", sig);
    }
    
    if( sig == SIGQUIT){        //如果是ctrl+\ 信号
        printf("\nI got signal id=%d, SIGQUIT\n", sig);
    }
}

int main(void)
{
    int i = 0; //用来计数
    struct sigaction act, oldact; 
    act.sa_handler = show_handler; //定义信号处理函数
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = SA_RESETHAND | SA_NODEFER; //设置信号处理的其他相关操作 SA_RESETHAND  调用信号处理函数时，将信号的处理函数重置为缺省值SIG_DFL  SA_NODEFER ：一般情况下， 当信号处理函数运行时，内核将阻塞该给定信号。但是如果设置了 SA_NODEFER标记， 那么在该信号处理函数运行时，内核将不会阻塞该信号

    sigaction(SIGINT, &act, &oldact);
    sigaction(SIGQUIT, &act, &oldact);
    while(1) {
        sleep(1);
        //printf("sleeping %d\n", i);
        i++;
    }
}
