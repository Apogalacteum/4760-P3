#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(int argc, char *argv[])
{	
	key_t key = ftok("shmfile", 65);
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	int *clockSec = (int) shmat(shmid,(void*)0,0);
	int *clockNano = (int) shmat(shmid,(void*)0,0);
	char *shmMsg = (char*) shmat(shmid,(void*)0,0);
	clockSec = 0;
	clockNano = 0;
	shmdt(&clockSec);
	shmdt(&clockNano);
	shmdt(shmMsg);
	
	int opt, time, i;
	pid_t cpid = 0;
	int maxChildProcesses = 5;
	int realTime = 5;
	char* logFile;

	while((opt = getopt(argc, argv, ":hs:l:t:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("HELP\n");
				printf("Options are: \n");
				printf(" -s x		where x is an integer for maximum number of child processes spawned.\n");
				printf(" -l filename	filename specifies the name for the log file.\n");
				printf(" -t z		where z is the time in real seconds when the master will terminate itself and all children.\n");
				break;
			case 's':
				printf("s with %s\n", optarg);
				maxChildProcesses = atoi(optarg);
				break;
			case 'l':
				printf("l with %s\n", optarg);
				logFile = optarg;
				break;
			case 't':
				printf("t with %s\n", optarg);
				realTime = atoi(optarg);
				break;
			case ':':
				printf("Option needs a value\n");
				break;
			case '?':
				printf("Unknown option: %c\n", optopt);
				break;
		}
	}
	for(; optind < argc; optind++)
	{
		printf("extra arguments: %s\n", argv[optind]);
	}
	
	for (i = 1; i < maxChildProcesses; i++)
	{
		if(cpid = fork())
			break;
	}

	if(cpid != 0)
	{
		while(clockSec < 2)
		{
			clockNano = clockNano + 5;
			if(shmMsg[0] != '\0')
				fprint("Message: %s\n", shmMsg);
			if(clockNano >= 1000000000)
			{
				clockNano = 0;
				clockSec = clockSec++;
			}
		}
	}

	printf("---\n");

	return 0;
}
