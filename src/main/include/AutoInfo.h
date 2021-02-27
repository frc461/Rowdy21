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
new MoveInfo(true,20,381),
new MoveInfo(false,58,150),
new MoveInfo(true,96,186),
new MoveInfo(false,40,41),
};
};