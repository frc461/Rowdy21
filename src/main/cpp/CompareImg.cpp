#include "CompareImg.h"

CompareImg::CompareImg() {
    cam.open(0);
    cam >> image;
}

int CompareImg::Compare() {
    int r = image.rows;
    int c = image.cols;
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            if (image.at<Vec3b>(i,j)) {
                return 0;
            }
        }
    }
    return 4;
}