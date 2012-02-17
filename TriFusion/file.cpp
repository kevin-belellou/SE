
#include <fstream>

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
          while(!ifile.eof()) {
			// Write in binary
               ofile.write((char*)&tmp, sizeof(int));
               // Read next value
               ifile >> tmp;
          }
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
          while(ifile.read((char*)&tmp, sizeof(int))) {
			// Write each value follow by a space
               ofile << tmp << " ";
          }
          ofile.close();
          ifile.close();

     }
}

