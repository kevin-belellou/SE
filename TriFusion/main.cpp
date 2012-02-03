#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

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
            std::cout << tmp << std::endl;
            //Use a space to not have a HUGE number
            //(but rather a number list)
            ofile.write((char*)&tmp, sizeof(int));
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

    //Read and put each number into value vector
    if(ifile) {
        //Set at the beginning of the file
        ifile.seekg(0);
        int tmp;
        while(ifile.read((char*)&tmp, sizeof(int))) {
            //std::cout << tmp << std::endl;
        }
        ifile.close();
    }

    return 0;
}
