#include <sstream>
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
     std::ifstream ifile(input.c_str(), std::ios::binary);

     unsigned int min = 0, max = 0;
     // Read
     if(ifile) {
          // Go to the end, tell us the size
          ifile.seekg(0, std::ios_base::end);
          max = (ifile.tellg() / sizeof(int)) - 1;
          ifile.close();
     }

     pid_t originalPID = getpid();

     // First part of the merging sort
     callFork(min, max, input, output);

     // Now only close buffer and all if I'm the original one
     if(originalPID == getpid()) {
          //Copy the last tmp file into the good one
          std::ofstream o(output.c_str());

          std::stringstream name;
          name << originalPID;
          std::ifstream i(name.str().c_str());
          int tmp;
          while(i.read((char*)&tmp, sizeof(int))) {
               o.write((char*)&tmp, sizeof(int));
          }
          // So now, values are now sorted and writted in _sorted.bin
          i.close();
          o.close();
          std::remove(name.str().c_str());
          std::cout << output << std::endl;
          createAnsiFile(output);
     }
     return 0;
}


