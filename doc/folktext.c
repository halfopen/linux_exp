#include <stdio.h>
int forkvar=0; 
int main() 
{
    int pid;
    pid = fork();    
    if (pid < 0 ) {    
         printf("failed \n");
         exit(1);        
     }
    else if (pid == 0 ) {    
         printf("I am the child process! %d\n ",getpid()); 
         forkvar = 1;
         printf("child, forkvar=%d \n", forkvar );
     }
    else {      //父进程执行
          wait();    //系统调用，等待子进程完成
          printf("I am the parent process! %d\n ",getpid());
          forkvar ++;
          printf("parent, forkvar=%d \n", forkvar );
     }    exit(0);
}