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
new MoveInfo(false,11,101),
new MoveInfo(true,41,47),
new MoveInfo(false,52,104),
new MoveInfo(true,51,70),
new MoveInfo(false,68,77),
};
};