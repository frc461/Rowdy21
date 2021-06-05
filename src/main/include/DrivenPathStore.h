#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Controls.h"

class DrivenPathStore {
public:
    DrivenPathStore();
    ~DrivenPathStore();

    void Write();

    void Store(double left, double right);
    void End();

private:
    std::ofstream writer;

    bool start;
};