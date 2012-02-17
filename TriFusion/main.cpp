#include <iostream>
#include <vector>
#include <fstream>

int callFork(unsigned int min, unsigned int max, const std::string& input, const std::string& output);

void createBinaryFile(const std::string& input);
void createAnsiFile(const std::string& input);

int main(int argc, char** argv)
{
     std::string input;
     std::string output;
     // Check arguments
     if(argc == 2) {
          input = output = argv[1];
     } else {
          std::cerr << "Wrong number of argument" << std::endl;
          return -1;
     }
     // Convert the plain text
     createBinaryFile(argv[1]);

     // Create filenames
     output += "_sorted.bin";
     input += "_random.bin";

     // Open files
     std::ofstream ofile(output.c_str(), std::ios::binary);
     std::ifstream ifile(input.c_str(), std::ios::binary);

     unsigned int min = 0, max = 0;
     // Read
     if(ifile) {
          // Go to the end, tell us the size
          ifile.seekg(0, std::ios_base::end);
          max = (ifile.tellg() / sizeof(int)) - 1;
          // And return at the beginning of the file
          ifile.seekg(0, std::ios::beg);
          int tmp;
          //std::cout << "The " << max + 1 << " values are: " << std::endl;
          while(ifile.read((char*)&tmp, sizeof(int))) {
               ofile.write((char*)&tmp, sizeof(int));
          }
          ofile.close();
          ifile.close();
     }

     pid_t originalPID = getpid();

     // First part of the merging sort
     //std::ifstream readedFile(input.c_str());
     callFork(min, max, input, output);

     // Now only close buffer and all if I'm the original one
     if(originalPID == getpid()) {
          //readedFile.close();

          //ofile.close();
          //ifile.close();

          // So now, file is now sorted and writted in _sorted.bin
          createAnsiFile(output);
     }
     return 0;
}


