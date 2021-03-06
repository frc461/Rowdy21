#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>

#include "cameraserver/CameraServer.h"

#include <iostream>

class CompareImg {
public:
    CompareImg();
    
    int Compare();

private:
    cs::UsbCamera *camera;

    cs::CvSource output;
    cs::CvSink *cvSink;

    cv::Mat image;
    cv::VideoCapture cam;

    bool can;

    int counter;
};