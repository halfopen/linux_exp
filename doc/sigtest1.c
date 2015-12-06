#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

static void  sig_usr(int signum)
{
	if(signum==36)
	{
		printf("sigusr1 \n");
	}else if(signum==38)
	{
		printf("sigusr2 \n");
	}else
	{
		printf("signal %d received\n",signum);
	}
}

int main()
{
	char buf[512];
	int n;
	struct sigaction sa_usr;
	sa_usr.sa_flags=0;
	sa_usr.sa_handler=sig_usr;

	sigaction(36,&sa_usr,NULL);
	sigaction(38,&sa_usr,NULL);
	printf("my pid %d \n",getpid());
	while(1)
	{
		if((n=read(STDIN_FILENO,buf,511))==-1)
		{
			if(errno==EINTR)
			{
				printf("read is interrupted by signal\n");

			}
		}else
		{
			buf[n]='\0';
			printf("%d bytes read %s\n",n,buf);
		}
	}
	return 0;

}
