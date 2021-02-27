#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>

class CompareImg {
public:
    CompareImg();
    
    int Compare();

private:
    cv::Mat image;
    cv::VideoCapture cam;
};