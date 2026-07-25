#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void displayProgramInformation(){
    std::cout<<"Camera colour tracker!\n";
}


int main(){
    displayProgramInformation();

    cv::VideoCapture camera{0};

    if (!camera.isOpened())
    {
        std::cerr << "Error: could not open camera.\n";
        return 2;
    }

    while(true){

        cv::Mat frame;
        camera.read(frame);
        if (frame.empty())
        {
            std::cerr << "Error: received an empty frame.\n";
            break;
        }

        const cv::Mat image{frame};

        cv::Mat resizedImage;

        cv::resize(
            image,
            resizedImage,
            cv::Size(),
            1.3,
            1.3,
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

        const cv::Mat kernel{
            cv::getStructuringElement(
                cv::MORPH_ELLIPSE,
                cv::Size{7, 7}
            )
        };

        cv::Mat cleanedMask;
        cv::morphologyEx(
            colourMask,
            cleanedMask,
            cv::MORPH_OPEN,
            kernel
        );
        cv::morphologyEx(
            cleanedMask,
            cleanedMask,
            cv::MORPH_CLOSE,
            kernel
        );

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(
            cleanedMask,
            contours,
            cv::RETR_EXTERNAL,
            cv::CHAIN_APPROX_SIMPLE
        );

        double largestArea{DBL_MIN};
        int indexOfArea{-1};
        for(std::size_t i{}; i < contours.size(); ++i){
            const double area{cv::contourArea(contours[i])};
            if(area > largestArea){
                largestArea = area;
                indexOfArea = static_cast<int>(i);
            }
        }

        cv::Mat finalImage{resizedImage.clone()};
        if(indexOfArea == -1){
            std::cout << "No object found!\n";
        }else{

            cv::Moments targetMoments{
                cv::moments(contours[indexOfArea])
            };

            if(targetMoments.m00 != 0.0)
            {
                const cv::Point targetCentre{
                    static_cast<int>(
                        targetMoments.m10 / targetMoments.m00
                    ),
                    static_cast<int>(
                        targetMoments.m01 / targetMoments.m00
                    )
                };
            
                cv::Point frameCentre{
                    resizedImage.cols / 2,
                    resizedImage.rows / 2
                };

                cv::drawMarker(
                    finalImage,
                    targetCentre,
                    cv::Scalar{0, 0, 255}
                );

                cv::drawMarker(
                    finalImage,
                    frameCentre,
                    cv::Scalar{0, 255, 0},
                    1
                );
                cv::line(
                    finalImage,
                    targetCentre,
                    frameCentre,
                    cv::Scalar(0, 255, 0),
                    2
                );

                int offsetX {frameCentre.x - targetCentre.x};
                int offsetY {frameCentre.y - targetCentre.y};
                std::string message = std::to_string(offsetX) + " " + std::to_string(offsetY);
                cv::putText(
                    finalImage,
                    message,
                    {targetCentre.x + ::abs(frameCentre.x - targetCentre.x)/2, targetCentre.y + ::abs(frameCentre.y - targetCentre.y)/2 - 10},
                    cv::FONT_HERSHEY_COMPLEX,
                    1,
                    cv::Scalar{0, 0, 255},
                    2
                );
            }
            cv::drawContours(
                finalImage,
                contours,
                indexOfArea,
                cv::Scalar{0, 0, 255},
                2
            );
        }
        cv::imshow("Original image", image);
        cv::imshow("Hsv image", hsvImage);
        cv::imshow("Colour mask", colourMask);
        cv::imshow("Cleaned mask", cleanedMask);
        cv::imshow("Final image", finalImage);

        const int key{cv::waitKey(1)};
        if (key == 'q' || key == 27)
        {
            break;
        }
        
        std::cout << "Image loaded successfully.\n";
        std::cout << "Width: " << image.cols << '\n';
        std::cout << "Height: " << image.rows << '\n';
        std::cout << "Channels image: " << image.channels() << '\n';
        std::cout << "Channels hsv: " << hsvImage.channels() << '\n';
        std::cout << "Channels mask: " << colourMask.channels() << '\n';
            
    }

    camera.release();
    cv::destroyAllWindows();

    return 0;
}

