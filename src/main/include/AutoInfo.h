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
new MoveInfo(true,0,375),
new MoveInfo(false,70,242),
new MoveInfo(true,100,171),
new MoveInfo(false,29,123),
};
};