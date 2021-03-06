#include "CompareImg.h"

CompareImg::CompareImg() {
    camera = new cs::UsbCamera("cam", 0);
    camera->SetResolution(4,3);
    camera->SetFPS(30);

    output = frc::CameraServer::GetInstance()->PutVideo("cam", 4, 3);
    cvSink = new cs::CvSink("cvsink");
    cvSink->SetSource(*camera);

    counter = 0;
}

//( ͡° ͜ʖ ͡°)
int CompareImg::Compare() {
    counter++;
    if (counter % 20 == 0) {
        cvSink->GrabFrame(image);
        output.PutFrame(image);

        int row = image.rows;
        int col = image.cols;
        
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < row; j++) {
                cv::Vec3b p = image.at<cv::Vec3b>(10,10);
                int b = p[0], g = p[1], r = p[2];

                if (g-r < 5 && b < 100) {
                    //std::cout << r << " " << g << " " << b << std::endl;
                    return 1;
                }
            }
        }
    }
    return (can) ? 4 : 10;
}