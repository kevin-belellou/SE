#include <fstream>
#include <iostream>

void createBinaryFile(const std::string& input)
{
     // Open file
     std::string output = input + "_random.bin";

     std::ofstream ofile(output.c_str(), std::ios::binary);
     std::ifstream ifile(input.c_str(), std::ios::binary);

	// If file is open
     if(ifile) {
		// Go to the beginning of the file
          ifile.seekg(0, std::ios::beg);
          int tmp = 0;
		// Read first value
          ifile >> tmp;
          std::cout << "The random values are : ";

          while(!ifile.eof()) {
               std::cout << tmp << " ";

			// Write in binary
               ofile.write((char*)&tmp, sizeof(int));
               // Read next value
               ifile >> tmp;
          }
          std::cout << std::endl;
          ofile.close();
          ifile.close();
     }
}

void createAnsiFile(const std::string& input)
{
     // Open file
     std::string output = input;
	output.resize(output.size()-4); // Remove the .bin

     std::ofstream ofile(output.c_str(), std::ios::binary);
     std::ifstream ifile(input.c_str(), std::ios::binary);

	// If file is open
     if(ifile) {
		// Go to the beginning of the file
          ifile.seekg(0, std::ios::beg);
          int tmp;
          std::cout << "The sorted values are : ";

          while(ifile.read((char*)&tmp, sizeof(int))) {
               std::cout << tmp << " ";

			// Write each value follow by a space
               ofile << tmp << " ";
          }
          std::cout << std::endl;
          ofile.close();
          ifile.close();
     }
}

