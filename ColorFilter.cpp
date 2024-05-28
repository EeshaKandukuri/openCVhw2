#include "ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {

    //PROBLEM 1
    //imshow("result", _frame);

    //PROBLEM 2: B
    //imshow("blue", _chans[0]);

    //PROBLEM 2: G
    //imshow("green", _chans[1]);

    //PROBLEM 2: R
    //imshow("red", _chans[2]);

    //PROBLEM 3: Blue Subtraction
    //imshow("blue subtraction", _chans[0]);

    //PROBLEM 3: Blue Threshold
    //imshow("blue threshold", _chans[0]);

    //PROBLEM 3: Largest Blue Blob
    //imshow("largest blue blob", _chans[0]);

    //PROBLEM 3: Blue Cup
    //imshow("blue cup", _chans[0]);

    //PROBLEM 3: Green Subtraction
    //imshow("green subtraction", _chans[1]);

    //PROBLEM 3: Green Threshold
    //imshow("green threshold", _chans[1]);

    ////PROBLEM 3: Largest Green Blob
    //imshow("largest green blob", _chans[1]);

    //PROBLEM 3: Green Cup
    //imshow("green cup", _chans[1]);

    //PROBLEM 3: Red Subtraction
    //imshow("red subtraction", _chans[2]);

    //PROBLEM 3: Red Threshold
    //imshow("red threshold", _chans[2]);

    ////PROBLEM 3: Largest Red Blob
    //imshow("largest red blob", _chans[2]);

    //PROBLEM 3: Red Cup
    imshow("red cup", _chans[2]);


    waitKey(100);
}

void ColorFilter::findBlue() {
    //4.3.1
    subtract(_chans[0], _chans[2], _chans[0]);

    //4.3.2
    threshold(_chans[0], _chans[0], 50, 255, cv::THRESH_BINARY);

    //4.3.3
    vector<cv::Mat> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_chans[0], contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    cv::Mat _zeros = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);

    //display mask
    drawContours(_zeros, contours, highest, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    //copyTo(_chans[0], _chans[0], _zeros);

    //display blue cup
    copyTo(_frame, _chans[0], _zeros);
     
    
}

void ColorFilter::findGreen() {
    subtract(_chans[1], _chans[0], _chans[1]);

    threshold(_chans[1], _chans[1], 50, 255, cv::THRESH_BINARY);

    vector<cv::Mat> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_chans[1], contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    cv::Mat _zeros = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);

    //display mask
    drawContours(_zeros, contours, highest, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    //copyTo(_chans[1], _chans[1], _zeros);

    //display green cup
    copyTo(_frame, _chans[1], _zeros);

}

void ColorFilter::findRed() {
    
    subtract(_chans[2], _chans[1], _chans[2]);

    threshold(_chans[2], _chans[2], 50, 255, cv::THRESH_BINARY);

    vector<cv::Mat> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_chans[2], contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    cv::Mat _zeros = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);

    //display mask
    drawContours(_zeros, contours, highest, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);
    copyTo(_chans[2], _chans[2], _zeros);

    //display red cup
    //copyTo(_frame, _chans[2], _zeros);
}

void ColorFilter::findBGR() {


}