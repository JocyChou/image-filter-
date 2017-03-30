////
////  main.cpp
////  ProgramAssignment1
////
////  Created by 周思雨 on 9/30/16.
////  Copyright © 2016 周思雨. All rights reserved.
////



#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
//#include <tr1/unordered_map>


using namespace cv;
using namespace std;

void convolve(Mat source, Mat filter, int iw, int ih, int fw, int fh){
    Mat conv = cvCreateMat(source.rows, source.cols, CV_8UC1);
    
    int samplei = 0;
    int samplej = 0;
    for (int i = 0; i < ih; i++){
        for (int j = 0; j < iw; j++){
            conv.at<uchar>(i, j) = 0;
            float f = 0;
            for (int m = 0; m < fh; m++){
                for (int n = 0; n < fw; n++){
                    samplei = i + m;
                    samplej = j - fw + 1 + n;
                    if (samplei >= 0 && samplei < ih && samplej >= 0 && samplej < iw){
                        f += (float)(source.at<uchar>(samplei, samplej)) * filter.at<float>(m,n);
                    }
                }
            }
            conv.at<uchar>(i, j) += (uchar)f;
            //cout << std::hex << (int)(source.at<uchar>(i, j)) << " " << f << " ";
            //cout << std::hex << (int)(conv.at<uchar>(i, j)) << endl;
        }
    }
    
    //for( int i = 0; i < fh; i++) {
    //    for( int j = 0; j < fw; j++) {
    //        cout << filter.at<float>( i, j );
    //    }
        
    //}
    
    cvNamedWindow("Original:", CV_WINDOW_AUTOSIZE);
    imshow("Original:", source);
    cvNamedWindow("Convoluted:", CV_WINDOW_AUTOSIZE);
    imshow("Convoluted", conv);
    imwrite("/Users/Jocy/Dropbox/2016 Fall/CSI 111/Program assignment/ProgramAssignment1/ProgramAssignment1/convoluted1Polarcities.jpg", conv);
    cvWaitKey(-1);
    cvDestroyAllWindows();
}

int main(int argc, char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    cv::Mat img = cv::imread(argv[1], 1);
    if (img.empty()) {
        std::cout << "Error : Image loading failed!" << std::endl;
        return -1;
    }
    cv::Mat source = cvCreateMat(img.rows, img.cols, CV_8UC1);
    if (img.channels() != 1){
        std::cout << "Warning : Input image is not a grayscale image" << std::endl;
        cv::cvtColor(img, source, CV_RGBA2GRAY);
        
    }
    cv::Mat filter = Mat(2, 2, CV_32F, Scalar(1.0/4));
    //cv::Mat filtertri = Mat(3, 3, CV_32F, Scalar(1.0/9));
    
    //cout << filtertri << endl;
    convolve(source, filter,source.cols, source.rows, filter.cols, filter.rows);
    //convolve(source, filtertri, source.cols, source.rows, filtertri.cols, filtertri.rows);
    return -1;
}
