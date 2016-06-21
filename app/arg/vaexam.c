#include <stdarg.h>
#include <stdio.h>

int sum(int, ...);

int main()
{
	printf("Sum of 15 and 56 = %d\n",  sum(2, 15, 56) );
	printf("Sum of 15 and 56 = %d\n",  sum(2, NULL) );
	printf("Sum of 15 and 56 = %d\n",  sum(2, 56) );
	printf("Sum of 15 and 56 = %d\n",  sum(2, 15, 56) );
	printf("Sum of 15 and 56 = %d\n",  sum(2, 15, 56, 0) );
	printf("Sum of 15 and 56 = %d\n",  sum(0, 15, 56, 0) );
	return 0;
}

int sum(int num_args, ...)
{
	int val = 0;
	va_list ap;
	int i;

	va_start(ap, num_args);
	for(i = 0; i < num_args; i++) 
	{
		int tmp=NULL;	
		tmp = va_arg(ap, int);
	//	if ((int *)tmp == NULL);
	//		break;
		if (tmp == 0)
			break;
		val += tmp;
	}
	va_end(ap);
	printf("count : %d", i);
	return val;
}
