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

    cv::Mat resizedImage;

    cv::resize(
        image,
        resizedImage,
        cv::Size(),
        0.8,
        0.8,
        cv::INTER_AREA
    );

    cv::Mat hsvImage;
    cv::cvtColor(
        resizedImage,
        hsvImage,
        cv::COLOR_BGR2HSV
    );

    cv::Mat colourMask;
    const cv::Scalar lowerBlue{90, 210, 210};
    const cv::Scalar upperBlue{107, 255, 255};
    cv::inRange(
        hsvImage,
        lowerBlue,
        upperBlue,
        colourMask
    );

    std::cout << "Image loaded successfully.\n";
    std::cout << "Width: " << image.cols << '\n';
    std::cout << "Height: " << image.rows << '\n';
    std::cout << "Channels image: " << image.channels() << '\n';
    std::cout << "Channels hsv: " << hsvImage.channels() << '\n';
    std::cout << "Channels mask: " << colourMask.channels() << '\n';

    cv::imshow("Original image", image);
    cv::imshow("Hsv image", hsvImage);
    cv::imshow("Colour mask", colourMask);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

