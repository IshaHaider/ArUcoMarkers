//
//  main.cpp
//  OpenCVTest
//
//  Created by Isha Haider on 2023-08-07.
//


#include <opencv2/opencv.hpp>
#include <iostream>
//could do: "using namespace cv;" but better to just put it manually

int showImageFromDisk(std::string imagePath) {
    cv::Mat image = cv::imread(imagePath);
    // process image
    //imread() reads the image from the argument provided
    //stores it in image object (Mat = standard data type of openCV's image (matrix))
    
    cv::imshow("Image from disk", image);
    //imshow("title of the image", image object)
    cv::waitKey();
    //imshow and waitKey must always be together
    //waitKey is a dela: allows users to display a window for given milliseconds or until any key is pressed
    return 0;
}



int showVideoFromDisk(std::string videoPath) {
    cv::VideoCapture videoCapture(videoPath);
    if (!videoCapture.isOpened()) {
        std::cout << "Error opening video stream of file" << std::endl;
        return -1;
    }
    while (true) {
        cv::Mat frame;
        videoCapture >> frame;
        // process frame here
        if (frame.empty()) break;
        cv::imshow("Video frame", frame);
        if (cv::waitKey(10) == 27) break;
    }
    videoCapture.release();
    cv::waitKey();
    return 0;
}

int streamWebcamFeed() {
    cv::VideoCapture videoCapture(0);
    //the parameter "0" or 1 or 2 means webcam (where integer value is the specific webcam you want to access)
    if (!videoCapture.isOpened()) {
        std::cout << "Unable to connect to webcam"  << std::endl;
        return -1;
    }
    while(true) {
        cv::Mat frame;
        videoCapture >> frame; //push the frames into the Mat object
        if(frame.empty()) break;
        cv::imshow("webcam", frame); //show and push out the frame
        if (cv::waitKey(10) >= 27) break;
        //if waitKey >= 0, waitKey returns an integer value based on the character/key you have pressed on the screen
        //waitKey(10) means 10 frames per millisecond?
    }
    videoCapture.release();
    return 0;
}

int main(int argc, const char * argv[]) {
    if (argc == 3) {
        std::string readType(argv[1]);
        std::string filePath(argv[2]);
        if (readType == "--image") {
            return showImageFromDisk(filePath);
        } else if (readType == "--video") {
            return showVideoFromDisk(filePath);
        } else {
            return streamWebcamFeed();
        }
    } else {
        return streamWebcamFeed();
    }
    return 0;
}
