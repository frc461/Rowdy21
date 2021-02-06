#pragma once
#include <vector>
class AutoInfo {
public:
class MoveInfo {
public:
MoveInfo(bool dir, float angle, float distance) {
this->dir = dir;
this->angle = angle;
this->distance = distance;
}
bool dir;
float angle;
float distance;
};
std::vector<MoveInfo*> list = {
new MoveInfo(true,0,200),
new MoveInfo(false,89,76),
new MoveInfo(true,89,217),
};
};