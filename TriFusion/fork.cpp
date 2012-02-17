#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int callFork(unsigned int min, unsigned int max, const std::string& input, const std::string& output)
{
     pid_t pid_courant = getpid();
     pid_t pid_pere;
     //printf("I'm the first process, number %d\n", pid_courant);

     int nbFils = 0;
     unsigned int minFils, maxFils;

     while (min < max && nbFils < 2) {
          for (int i = 1; i <= 2; i++) {
               pid_pere = pid_courant;

               // Determining intervals for each son
               if (i == 1) {
                    minFils = min;
                    maxFils = (min + max) / 2;
               } else {
                    minFils = ((min + max) / 2) + 1;
                    maxFils = max;
               }

               // Son's creation
               switch(fork()) {
               case 0: // Son's code
                    // Value's update
                    pid_courant = getpid();
                    min = minFils;
                    max = maxFils;
		          nbFils = 0;
                    //printf("%d Created %d (%d/2); Interval : %d - %d\n", pid_pere, pid_courant, i, min, max);
                    break;
               default: // Father's code
                    nbFils++;
                    break;
               }
               if (getpid() != pid_pere) // If I'm the first son
                    break;
          }
     }

     // If I'm a father
     if (pid_pere == pid_courant) {
          //printf("%d : Waiting\n", pid_courant);

          // Wait until sons finished
          pid_t process;
          for (int j = 1; j <= 2; j++) {
               process = wait(NULL);
               //printf("%d : %d ended (%d/2)\n", pid_courant, process, j);
          }

          //printf("%d : Wait end\n", pid_courant);

          // Sorting
          //std::ifstream readedFile(output.c_str(), std::ios::binary); // Open file_random.bin
          //std::ofstream writedFile(output.c_str(), std::ios::binary | std::ios::app); // Open file_sorted.bin
          std::fstream fichier(output.c_str(), std::ios_base::binary | std::ios_base::in | std::ios_base::out);

          //int tmp;
          printf("\n%d interval %d - %d\n", pid_courant, min, max);
          //printf("1st son's interval\n");
          //for (unsigned int k = min * sizeof(int); k <= max * sizeof(int); k += sizeof(int))
          //{
               //if (k == (((min + max) / 2) + 1) * sizeof(int))
                    //printf("2nd son's interval\n");
               //readedFile.seekg(k, std::ios::beg);
               //readedFile.read((char*)&tmp, sizeof(int));
               //printf("----------> %d\n", tmp);
          //}

          unsigned int leftInterval = min;
          unsigned int rightInterval = ((min + max) / 2) + 1;
          int nb1, nb2;
          int pos = 0;

          int initPosLeft;
          int initPosRight;
          int buffer;

          while (leftInterval <= (min + max) / 2 && rightInterval <= max) {
               // Read the 1st number of the 1st list
               initPosLeft = leftInterval * sizeof(int);
               fichier.seekg(initPosLeft, std::ios::beg);
               fichier.read((char*)&nb1, sizeof(int));

               // Read the 1st number of the 2nd list
               initPosRight = rightInterval * sizeof(int);
               fichier.seekg(initPosRight, std::ios::beg);
               fichier.read((char*)&nb2, sizeof(int));

               
               // 
               //fichier.seekp((min + pos) * sizeof(int), std::ios::beg);

               int posFile = fichier.tellp();
               if (nb1 <= nb2) {  
/*
                    printf("%d <= %d (%d)\n", nb1, nb2, posFile);
                    fichier.seekg(initPosRight, std::ios::beg);                    
                    fichier.write((char*)&nb1, sizeof(int));
                    fichier.flush();
*/
                    leftInterval++;               
               } else {
                    printf("%d > %d (%d)\n", nb1, nb2, posFile);
                    buffer = nb1;
                    
                    fichier.seekp(initPosLeft, std::ios::beg);    
                    fichier.write((char*)&nb2, sizeof(int));
                    fichier.flush();

                    fichier.seekp(initPosRight, std::ios::beg);    
                    fichier.write((char*)&buffer, sizeof(int));
                    fichier.flush();
                    rightInterval++;
               }
               pos++;
          }
/*
          std::cout << "Condition: " << leftInterval << " " << (min+max)/2 << std::endl;
          if (leftInterval > (min + max) / 2) {
               for (int i = rightInterval; rightInterval <= max; rightInterval++) {
                    fichier.seekg(i * sizeof(int), std::ios::beg);
                    fichier.read((char*)&nb2, sizeof(int));
                    printf("(1) j'ecris %d\n", nb2);

                    fichier.seekp((min + pos) * sizeof(int), std::ios::beg);
                    fichier.write((char*)&nb2, sizeof(int));
                    fichier.flush();

                    pos++;
               }
          } else {
               std::cout << leftInterval << std::endl;
               for (int i = leftInterval; leftInterval <= (min + max) / 2; leftInterval++) {
                    fichier.seekg(i * sizeof(int), std::ios::beg);
                    fichier.read((char*)&nb1, sizeof(int));

                    printf("(2) j'ecris %d\n", nb1);
                    fichier.seekp((min + pos) * sizeof(int), std::ios::beg);
                    fichier.write((char*)&nb1, sizeof(int));
                    fichier.flush();

                    pos++;
               }
          }
//*/

          fichier.close();
          fichier.close();
     }
     return 0;
}
