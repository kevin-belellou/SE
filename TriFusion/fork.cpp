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
          std::ifstream readedFile(output.c_str(), std::ios::binary); // Open file_random.bin
          std::ofstream writedFile(output.c_str(), std::ios::binary | std::ios::app); // Open file_sorted.bin

          //int tmp;
          printf("\n\n\n%d interval %d - %d\n", pid_courant, min, max);
          //printf("1st son's interval\n");
          //for (unsigned int k = min * sizeof(int); k <= max * sizeof(int); k += sizeof(int))
          //{
               //if (k == (((min + max) / 2) + 1) * sizeof(int))
                    //printf("2nd son's interval\n");
               //readedFile.seekg(k, std::ios::beg);
               //readedFile.read((char*)&tmp, sizeof(int));
               //printf("----------> %d\n", tmp);
          //}

          unsigned int i1, i2;
          i1 = min;
          i2 = ((min + max) / 2) + 1;
          int nb1, nb2, pos;
          pos = 0;

          while (i1 <= (min + max) / 2 && i2 <= max) {
               // Read the 1st number of the 1st list
               readedFile.seekg(i1 * sizeof(int), std::ios::beg);
               readedFile.read((char*)&nb1, sizeof(int));

               // Read the 1st number of the 2nd list
               readedFile.seekg(i2 * sizeof(int), std::ios::beg);
               readedFile.read((char*)&nb2, sizeof(int));
               
               // 
               writedFile.seekp((min + pos) * sizeof(int), std::ios::beg);

               int posFile = writedFile.tellp();
               if (nb1 <= nb2) {  
                    printf("%d <= %d (%d)\n", nb1, nb2, posFile);
                    writedFile.write((char*)&nb1, sizeof(int));
                    i1++;               
               } else {
                    printf("%d > %d (%d)\n", nb1, nb2, posFile);
                    writedFile.write((char*)&nb2, sizeof(int));
                    i2++;
               }
               pos++;
          }

          if (i1 > (min + max) / 2) {
               for (i2 = i2; i2 <= max; i2++) {
                    readedFile.seekg(i2 * sizeof(int), std::ios::beg);
                    readedFile.read((char*)&nb2, sizeof(int));
                    printf("j'ecris %d\n", nb2);

                    writedFile.seekp((min + pos) * sizeof(int), std::ios::beg);
                    writedFile.write((char*)&nb2, sizeof(int));

                    pos++;
               }
          } else {
               for (i1 = i1; i1 <= (min + max) / 2; i1++) {
                    readedFile.seekg(i1 * sizeof(int), std::ios::beg);
                    readedFile.read((char*)&nb1, sizeof(int));

                    printf("j'ecris %d\n", nb1);
                    writedFile.seekp((min + pos) * sizeof(int), std::ios::beg);
                    writedFile.write((char*)&nb1, sizeof(int));

                    pos++;
               }
          }

          readedFile.close();
          writedFile.close();
     }
     return 0;
}
