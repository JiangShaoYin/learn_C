#include <stdio.h>

int JudgeArgs(int args,int input_num)
{
	if(args	< input_num)
	{
		perror("args");		
		return -1;
	}
	return 0;
}
