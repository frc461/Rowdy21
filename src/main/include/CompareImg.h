#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>

#include "cameraserver/CameraServer.h"

#include <iostream>
#include <thread>

class CompareImg {
public:
    CompareImg();
    
    int Compare();

    void StartGetImage();
    void GetImage();

    void SetImageGrabbed(bool a);
    bool GetImageGrabbed();

    void ResetImage();

    void StartPutImage();
    void PutImageToSDB();

private:
    cs::UsbCamera *camera;

    cs::CvSource output;
    cs::CvSink *cvSink;

    cv::Mat image;

    bool can;
    bool imageGrabbed;

    std::thread getImage;
    std::thread putImage;
};