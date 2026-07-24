#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

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

    const std::string imagePath {argv[1]};

    std::cout<<"Provided image path: "<< imagePath << '\n';

    const cv::Mat image{
        cv::imread(imagePath, cv::IMREAD_COLOR)
    };

    if (image.empty())
    {
        std::cerr << "Error: could not load image: " << imagePath << '\n';
        return 2;
    }

    cv::Mat grayscaleImage;
    cv::cvtColor(
        image,
        grayscaleImage,
        cv::COLOR_BGR2GRAY
    );

    cv::imshow("Original image", image);
    cv::imshow("Grayscale image", grayscaleImage);

    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Image loaded successfully.\n";
    std::cout << "Width: " << image.cols << '\n';
    std::cout << "Height: " << image.rows << '\n';
    std::cout << "Channels: " << image.channels() << '\n';

    return 0;
}

