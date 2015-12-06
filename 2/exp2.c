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
    if( sig == SIGINT){
        printf("\nI got signal id=%d, SIGINT\n", sig);
    }
    
    if( sig == SIGQUIT){
        printf("\nI got signal id=%d, SIGQUIT\n", sig);
    }
}

int main(void)
{
    int i = 0;
    struct sigaction act, oldact;
    act.sa_handler = show_handler;
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = SA_RESETHAND | SA_NODEFER; 

    sigaction(SIGINT, &act, &oldact);
    sigaction(SIGQUIT, &act, &oldact);
    while(1) {
        sleep(1);
        //printf("sleeping %d\n", i);
        i++;
    }
}
