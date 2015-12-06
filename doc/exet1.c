#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
char command[256];
void main()
{
	int rtn;
	while(1)
	{
		printf(">");
		fgets(command,256,stdin);
		command[strlen(command)-1]=0;
		if(fork()==0)
		{
			execlp(command,NULL);
			perror(command);
			exit(errno);

		}else
		{
			wait(&rtn);
			printf("child process return %d\n",rtn);
		}
	}
	
}