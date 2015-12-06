#include <stdio.h>    // for printf()  
 
#include <unistd.h>   // for pause()  
 
#include <signal.h>   // for signal()  
 
#include <string.h>   // for memset()  
 
#include <sys/time.h> // struct itimeral. setitimer()  
void printMsg(int);  
  
  
  
int main() {  
  
  // Get system call result to determine successful or failed  
  
  int res = 0;  
  
  // Register printMsg to SIGALRM  
  
  signal(SIGALRM, printMsg);  
  
    
  
  struct itimerval tick;  
  
  // Initialize struct  
  
  memset(&tick, 0, sizeof(tick));  
  
  // Timeout to run function first time  
  
  tick.it_value.tv_sec = 1;  // sec  
  
  tick.it_value.tv_usec = 0; // micro sec.  
  
  // Interval time to run function  
  
  tick.it_interval.tv_sec = 1;  
  
  tick.it_interval.tv_usec = 0;  
  
  // Set timer, ITIMER_REAL : real-time to decrease timer,  
  
  //                          send SIGALRM when timeout  
  
  res = setitimer(ITIMER_REAL, &tick, NULL);  
  
  if (res) {  
  
    printf("Set timer failed!!/n");  
  
  }  
  
  
  
  // Always sleep to catch SIGALRM signal  
  
  while(1) {  
  
    pause();  
  
  }  
  
  
  
  return 0;    
  
}  
  
  
  
void printMsg(int num) {  
  
  printf("%s","Hello World!!\n");  
  
}  

/*
当setitimer()所执行的timer时间到了，会呼叫SIGALRM signal，所以在第30行用signal()将要执行的function指定给SIGALRM。 在第43行呼叫setitimer()设定timer，但setitimer()第二个参数是sturct，负责设定timeout时间，所以第36行到第 40行设定此struct。itimerval.it_value设定第一次执行function所延迟的秒数， itimerval.it_interval设定以后每几秒执行function，所以若只想延迟一段时间执行function，只要设定 itimerval.it_value即可，若要设定间格一段时间就执行function，则it_value和it_interval都要设定，否则 funtion的第一次无法执行，就别说以后的间隔执行了。 第36行和第39行的tv_sec为sec，第37行和40行为micro sec(0.001 sec)。 第43行的第一个参数ITIMER_REAL，表示以real-time方式减少timer，在timeout时会送出SIGALRM signal。第三个参数会存放旧的timeout值，如果不需要的话，指定NULL即可。 第47 行的pause()，命令系统进入sleep状态，等待任何signal，一定要用while(1)无穷循环执行pause()，如此才能一直接收 SIGALRM signal以间隔执行function，若拿掉while(1)，则function只会执行一次而已。
*/