#include <stdio.h>
int main(int argc, char const *argv[])
{
	/* code */
	int i;
	if(fork()==0)
	{
		for(i=1;i<10;i++)
		{
			printf("BBB\n");
		}
	}else
	{
		for(i=1;i<10;i++)
		{
			printf("AAA\n");
		}
	}
	return 0;
}