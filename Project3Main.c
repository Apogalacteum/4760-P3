#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	int opt, time;

	while((opt = getopt(argc, argv, "hs:l:t:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("help\n");
				break;
			case 's':
				printf("s\n");
				break;
			case 'l':
				printf("l\n");
				break;
			case 't':
				printf("t\n");
				break;
			case ':':
				printf("Option needs a value\n");
				break;
			case '?':
				printf("Unknown option: \n");
				break;
		}
	}
}
