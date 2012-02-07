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
     return 0;
}

int callFork(int min, int max) {
     pid_t son = fork();
	switch(son) {
	case 0:
          std::cout << "Fork success for value: " << min << "/" << max << " (" << getpid() << ")" << std::endl;
          if(min >= max) {
               int val = 0;
               readedFile.seekg(max * sizeof(int));
               readedFile.read((char*)&val, sizeof(int));
               std::cout << "So value is: " << val << std::endl;
               return val;
          } else {
               callFork(min, max/2);
          	wait(NULL);
          }
          return 0;
     default:
          callFork(max/2+1, max);
          wait(NULL);
          std::cout << "Son fork ended : " << son << std::endl;
     }
     return 0;
}

int doSonFork(int min, int max)
{
     //Son's code

}
