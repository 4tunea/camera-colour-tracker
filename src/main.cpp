#include <iostream>

void displayProgramInformation(){
    std::cout<<"Camera colour tracker!\n";
    std::cout<<"Usage: colour_tracker <image_path>\n";
}

int main(int argc, char* argv[]){
    displayProgramInformation();

    if (argc < 2){
        std::cerr<<"Error: no image path provided.\n";
        return 1;
    }

    const char* imagePath = argv[1];

    std::cout<<"Provided image path: "<< imagePath << '\n';

    return 0;
}