#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void sigroutine(int dunno)
{
	switch(dunno)
	{
		case 1:
		printf("Get a signal - SIGHUP");
		break;
		case 2:
		printf("Get a signal-SIGINT");
		break;
		case 3:
		printf("Get a signal - SIGQUIT");
		break;
	}
	return;
}
int main()
{
	printf("process id is %d",getpid());
	signal(1,sigroutine);
	signal(2,sigroutine);
	signal(3,sigroutine);
	sleep(1000*30);
	 return 0;
	
}