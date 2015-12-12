/*************************************************************************
	> File Name: exp1.c
	> Author: 计科三班2013301500100秦贤康
	> Mail: qinxiankang@gmail.com
	> Created Time: 2015年12月05日 星期六 21时23分52秒
 ************************************************************************/

/*实现一个信号接收程序。其中信号安装为sigaction（）函数。设定sa_flags=SA_SIGINFO，并为sa_sigaction指定处理函数，该处理函数为显示接收信号的ID。*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

//显示接收信号的ID
static void sig_usr(int signum)
{
    printf("recieved a signal，signal id is:%d\n", signum);
}

int main(void)
{
    char buf[512];
    int  n;
    struct sigaction sa_usr;
    sa_usr.sa_flags = SA_SIGINFO;
    sa_usr.sa_handler = sig_usr;   //信号处理函数
    
    sigaction(SIGUSR1, &sa_usr, NULL);
    
    printf("My PID is %d\n", getpid()); //输出当前进程pid
    
    while(1)
    {
        if((n = read(STDIN_FILENO, buf, 511)) == -1)
        {
            if(errno == EINTR)
            {
                printf("read is interrupted by signal\n");
            }
        }
        else
        {
            buf[n] = '\0';
            printf("%d bytes read: %s\n", n, buf);
        }
    }
    
    return 0;
}
