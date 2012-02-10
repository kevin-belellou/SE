#include <iostream>
#include <fstream>
#include <vector>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	pid_t pid_courant = getpid();
	pid_t pid_pere;
	printf("Je suis le processus %d\n", pid_courant);

	int nbTab = 3;
	int nbFils = 0;
	while (nbTab > 1 && nbFils < 2)
	{
		for (int i = 0; i < 2; i++)
		{
			pid_pere = pid_courant;
			printf("%d :\n", pid_courant);
			switch(fork())
			{
				case 0:
					pid_courant = getpid();
					printf("%d cree %d \n", pid_pere, pid_courant);
					break;
				default:
					nbFils++;
					break;
				
			}
			if (getpid() != pid_pere)
				break;
		}
		nbTab--;
	}

	printf("%d : OK\n", getpid());
	
	if (pid_pere == pid_courant)
	{
		printf("%d : j'attends\n", pid_courant);

		//pid_t retWait = 0;
		while (wait(NULL) != -1)
		{
			printf("%d : un process s'est fini\n", pid_courant);
		}

		printf("%d : attente finie\n", pid_courant);
	}
	
	return 0;
}
