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
std::vector<ra*> list = {
new MoveInfo(false,0,150),
new MoveInfo(true,23,130),
new MoveInfo(false,97,242),
new MoveInfo(true,71,240),
};
std::vector<rb*> list = {
new MoveInfo(false,23,170),
new MoveInfo(true,65,190),
new MoveInfo(false,95,213),
new MoveInfo(true,45,229),
}
};

std::vector<ba*> list = {
new MoveInfo(true,23.5,380),
new MoveInfo(false,94,222),
new MoveInfo(true,110,150),
new MoveInfo(false,40,50),
}

std::vector<bb*> list = {
new MoveInfo(true,20,381),
new MoveInfo(false,58,150),
new MoveInfo(true,96,186),
new MoveInfo(false,40,41),
}