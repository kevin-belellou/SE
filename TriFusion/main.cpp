#include <iostream>
#include <fstream>
#include <vector>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int callFork(int min, int max);

std::ifstream readedFile;
void createBinaryFile(const std::string& input)
{
     //Open file
     std::string output = input + "_random.bin";

     std::ofstream ofile(output.c_str(), std::ios::binary);
     std::ifstream ifile(input.c_str(), std::ios::binary);

     //Read and put each number into value vector
     //If we can't read the file, we won't convert anything
     if(ifile) {
          int tmp = 0;
          ifile >> tmp;
          while(!ifile.eof()) {
               //Use a space to not have a HUGE number
               //(but rather a number list)
               ofile.write((char*)&tmp, sizeof(int));
               //Read next value
               ifile >> tmp;
          }
          ofile.close();
          ifile.close();

     }
}


int main(int argc, char** argv)
{
     std::string input;
     std::string output;
     //Check argument
     if(argc == 2) {
          input = output = argv[1];
     } else {
          std::cerr << "Wrong number of argument" << std::endl;
          return -1;
     }
     //Convert the plain text
     createBinaryFile(argv[1]);

     //Create filename
     output += "_sorted.bin";
     input += "_random.bin";

     //Open file
     std::ofstream ofile(output.c_str(), std::ios::binary);
     std::ifstream ifile(input.c_str(), std::ios::binary);


     unsigned int min = 0, max = 0;
     //Read
     if(ifile) {
          //Go to the end, tell us the size
          ifile.seekg(0, std::ios_base::end);
          max = ifile.tellg();
          //And return at the beginning of the file
          ifile.seekg(0, std::ios::beg);
          int tmp;
          std::cout << "Value are: " << std::endl;
          while(ifile.read((char*)&tmp, sizeof(int))) {
               std::cout << tmp << std::endl;
          }
     }

     //First part of the merging sort
     readedFile.open(input.c_str());
     callFork(min, max);
     readedFile.close();

     ofile.close();
     ifile.close();

     //So now, file is now sorted and writted in _sorted.bin
     //Maybe write it to a readable file ?
     return 0;
}

int callFork(int min, int max)
{
     pid_t pid_courant = getpid();
     pid_t pid_pere;
     printf("Je suis le processus %d\n", pid_courant);

     int nbFils = 0;
     int minFils, maxFils;

     while (min < max && nbFils < 2) {
          for (int i = 1; i <= 2; i++) {
               pid_pere = pid_courant;

               // Determination des intervalles pour chaque fils
               if (i == 1) {
                    minFils = min;
                    maxFils = (min + max) / 2;
               } else {
                    minFils = ((min + max) / 2) + 1;
                    maxFils = max;
               }

               // Creation des fils
               switch(fork()) {
               case 0: // Fils
                    // Mise a jour des valeurs
                    pid_courant = getpid();
                    min = minFils;
                    max = maxFils;
                    printf("%d Created %d (%d/2); Interval : %d - %d\n", pid_pere, pid_courant, i, min, max);
                    break;
               default: // Pere
                    nbFils++;
                    break;
               }
               if (getpid() != pid_pere) // Si je suis le 1er fils
                    break;
          }
     }

	//If i'm the father
     if (pid_pere == pid_courant) { 
          printf("%d : Waiting\n", pid_courant);

		//Wait until son finished
          pid_t process;
          for (int j = 1; j <= 2; j++) { 
               process = wait(NULL);
               printf("%d : %d ended (%d/2)\n", pid_courant, process, j);
          }

          printf("%d : Wait end\n", pid_courant);
          //
     }

	return 0;
}
