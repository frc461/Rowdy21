#include "CompareImg.h"

CompareImg::CompareImg() {
    camera = new cs::UsbCamera("cam", 0);

    camera->SetResolution(40,30);
    camera->SetFPS(30);

    output = frc::CameraServer::GetInstance()->PutVideo("cam", 40, 30);

    imageGrabbed = false;

    if (camera->IsConnected()) can = true; 
    else {
        can = false;
        std::cout << "NO CAM BRO" << std::endl;
    }
    cvSink = new cs::CvSink("cvsink");
    cvSink->SetSource(*camera);
}

void CompareImg::ResetImage() {
    cv::Mat i;
    image = i;
}

void CompareImg::StartPutImage() {
    putImage = std::thread(&CompareImg::PutImageToSDB, this);
    putImage.detach();
}
void CompareImg::PutImageToSDB() {
    while (true) {
        cvSink->GrabFrame(image);
        if (!image.empty()) output.PutFrame(image);
    }
}

void CompareImg::StartGetImage() {
    getImage = std::thread(&CompareImg::GetImage, this);
    getImage.detach();
}
void CompareImg::GetImage() {
    while (image.empty()) {
        std::cout << "GETTING IMG" << std::endl;
        cvSink->GrabFrame(image);
    }
    std::cout << "GOT IMG" << std::endl;
    imageGrabbed = true;
}

void CompareImg::SetImageGrabbed(bool a) {
    imageGrabbed = a;
}

bool CompareImg::GetImageGrabbed() {
    return imageGrabbed;
}

//( ͡° ͜ʖ ͡°)
int CompareImg::Compare() {
    if (imageGrabbed) {
        int r = image.rows;
        int c = image.cols;
        // r: 90 | c: 160
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cv::Vec3b p = image.at<cv::Vec3b>(i,j);
                int b = p[0], g = p[1], r = p[2];

                bool yellow = (g-r < 5 && b < 150 && g-b > 80);
                
                if (yellow) {
                    if (j < 160 && j > 125) { //blue (a red)
                        return 0;
                    }
                    else if (j < 96 && j > 60) { //yellow (b red)
                        return 1;
                    }
                    else if (j < 65 && j > 41) { //red (b blue)
                        std::cout << r << " " << g << " " << b << std::endl;
                        return 2;
                    }
                    else if (j < 41) { //white (a blue)
                        return 3;
                    }
                }
            }
        }
        std::cout << "Nothing found" << std::endl;
        return (can) ? 4 : -1;
    }
    return -2;
}