#include <iostream>
#include <fstream>
#include <vector>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	pid_t polo = getpid();
	pid_t sauvPolo;
	printf("Je suis le processus %d\n", polo);

	int nbTab = 3;
	int nbFils = 0;
	while (nbTab > 1 && nbFils < 2)
	{
		for (int i = 0; i < 2; i++)
		{
			sauvPolo = polo;
			printf("%d :\n", polo);
			switch(fork())
			{
				case 0:
					polo = getpid();
					printf("%d cree %d \n", sauvPolo, polo);
					goto boucle;
				default:
					nbFils++;
					break;
				
			}
		}
		boucle: nbTab--;
	}

	printf("%d : OK\n", getpid());
	
	if (sauvPolo == polo)
	{
		printf("%d : j'attends\n", polo);

		//pid_t retWait = 0;
		while (wait(NULL) != -1)
		{
			printf("%d : un process s'est fini\n", polo);
		}

		printf("%d : attente finie\n", polo);
	}
	
	return 0;
}
