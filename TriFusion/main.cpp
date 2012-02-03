#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

void createBinaryFile(const std::string& input) {
	//Open file
	std::string output = input + "_random.bin";

	std::ofstream ofile(output.c_str(), std::ios::binary);
	std::ifstream ifile(input.c_str(), std::ios::binary);

	std::vector<int> value;
	//Read and put each number into value vector
	//If we can't read the file, we won't convert anything
	if(ifile) {
		int tmp;	
		while(!ifile.eof()) {
			ifile >> tmp;
			value.push_back(tmp);
		}
		ifile.close();

	//Now we have our value, write them
	if(ofile) {
		//We are going to read data back to front
		//So, reverse our vector
		std::reverse(value.begin(), value.end());
		while(!value.empty()) {
			//Use a space to not have a HUGE number
			//(but rather a number list)
			ofile.write((char*)&value.back(), sizeof(int));
			value.pop_back();
		}
		ofile.close();
	}
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

	std::vector<int> value;
	//Read and put each number into value vector
	if(ifile) {
		//Set at the beginning of the file
		ifile.seekg(0);
		char* tmp;
		while(!ifile.eof()) {
			ifile.read(tmp, sizeof(int));
			std::cout << tmp << std::endl;
		}
		ifile.close();
	}

	return 0;
}
