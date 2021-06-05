#include "DrivenPathStore.h"

DrivenPathStore::DrivenPathStore()
{
    start = false;
}

DrivenPathStore::~DrivenPathStore() {}

void DrivenPathStore::Store(double left, double right)
{
    if (!start) {
        writer.open("/home/lvuser/info.txt");
        start = true;
    }

    std::stringstream ss;
    ss << left << " " << right << "\n";
    writer << ss.str();
}

void DrivenPathStore::End()
{
    writer.close();
}