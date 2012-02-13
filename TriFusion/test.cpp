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

	//int nbTab = 3;
	int nbFils = 0;

	int min = 0, max = 3;
	int minFils, maxFils;

	while (min < max && nbFils < 2)
	{
		for (int i = 1; i <= 2; i++)
		{
			pid_pere = pid_courant;
			// printf("%d :\n", pid_courant);

			if (i == 1)
			{
				minFils = min;
				maxFils = (min + max) / 2;
			}
			else
			{
				minFils = ((min + max) / 2) + 1;
				maxFils = max;
			}

			switch(fork())
			{
				case 0: // Fils
					pid_courant = getpid();
					min = minFils;
					max = maxFils;
					printf("%d cree %d (%d/2); valeurs : %d - %d\n", pid_pere, pid_courant, i, min, max);
					break;
				default: // Pere
					nbFils++;
					break;
				
			}
			if (getpid() != pid_pere) // Si je suis le 1er fils
				break;
		}
		//nbTab--;
	}

	// printf("%d : OK\n", getpid());
	
	if (pid_pere == pid_courant) // Si je suis un pere
	{
		printf("%d : j'attends\n", pid_courant);

		pid_t process;
		for (int j = 1; j <= 2; j++)
		{
			process = wait(NULL);
			printf("%d : le process %d s'est fini (%d/2)\n", pid_courant, process, j);
		}

		printf("%d : attente finie\n", pid_courant);
	}
	
	return 0;
}
