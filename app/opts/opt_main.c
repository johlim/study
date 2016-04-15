#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // exit

#define VERSION "0.0.1"
void print_help();

int main(int argc, char * argv[])
{
	int index,c;

	opterr = 0;

	if (argc == 1)
		print_help();
	while(( c = getopt(argc, argv, "hvf:")) != -1)
		switch (c)
		{
			case 'h':
				print_help();
				exit(0);
				break;
			case 'v':
				printf("testopt %s\n", VERSION);
				exit(0);
				break;
			case 'f':
				printf("File : %s\n", optarg);
				break;
			case '?':
				fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				print_help();
				exit(1);
		}

	for(index = optind; index < argc ; index++)
		printf("Non-option argument %s\n", argv[index]);
}

void print_help(void)
{
	printf("testopt (ver.%s) is a getopt example.\n", VERSION);
	printf("testopt [-h] [-v] [-f FILE] \n\n");
	printf(" -h print this help and exit\n");
	printf(" -v print version and exit\n");
	printf(" -f FILE set file \n");
}
