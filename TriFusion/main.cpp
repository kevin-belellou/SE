#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        while(ifile.read((char*)&tmp, sizeof(int))) {
            //Do some stuff with data
        }
    }

	pid_t son;
	switch(son = fork()) {
    case -1:
        //Seems something went wrong
        std::cerr << "Fork failed" << std::endl;
        return(-1);
    case 0:
        //Son's code
        std::cout << "Fork success: " << getpid() << std::endl;
		break;
    default:
        //I am your father
        wait(NULL);
        std::cout << "Son fork ended" << std::endl;
    }

    ofile.close();
    ifile.close();
    return 0;
}
