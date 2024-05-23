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
    _chans = vector<cv::Mat>;
    split(_frame, _chans);
}

void ColorFilter::showResult() {
    //imshow("result", _frame);
    waitKey(1);
    //PROBLEM 2: B
    //imshow("blue", _chans[0]);
    //PROBLEM 2: G
    //imshow("green", _chans[1]);
    //PROBLEM 2: R
    //imshow("red", _chans[2]);

    //PROBLEM 3: Blue Subtraction
    //imshow("blue sub", _chans[0]);
    //PROBLEM 3: Green Subtraction
    //imshow("green sub", _chans[1]);
    //PROBLEM 3: Red Subtraction
    //imshow("red sub", _chans[2]);
}

void ColorFilter::findBlue() {

    //4.3.1
    subtract(_chans[0], _chans[2], bMinusR);

    //4.3.2
    //SAVE FOR LATER

    //4.3.3
    vector<cv::Mat> contours;
    vector<cv:Vec4i> hierarchy;
    findContours(_chans[0], contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;
    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    cv::Mat _zeros = zeros();
    drawContours(zeros, contours, highest, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierachy);
}

void ColorFilter::findGreen() {
    subtract(_chans[1], _chans[2], gMinusR);
}

void ColorFilter::findRed() {
    subtract(_chans[2], _chans[0], rMinusB);
}

void ColorFilter::findBGR() {

}