#pragma once
#include <vector>


class AutoInfo {
public:
    AutoInfo(int a){
        if(a == 0) list = rb;
        if(a == 1) list = ra;
        if(a == 2) list = bb;
        if(a == 3) list = ba;
    }

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
    std::vector<MoveInfo*> list = {};

private:
    std::vector<MoveInfo*> ra = { // GOOD
        new MoveInfo(false,0,150),
        new MoveInfo(true,23,95),
        new MoveInfo(false,95,200),
        new MoveInfo(true,75,275),
    };

    std::vector<MoveInfo*> rb = { // GOOD
        new MoveInfo(false,22,170),
        new MoveInfo(true,61,190),
        new MoveInfo(false,100,213),
        new MoveInfo(true,49,229),
    };

    std::vector<MoveInfo*> ba = { // GOOD
        new MoveInfo(true,24,360),
        new MoveInfo(false,90,222),
        new MoveInfo(true,110,150),
        new MoveInfo(false,40,70),
    };

    std::vector<MoveInfo*> bb = { // GOOD
        new MoveInfo(true,20,381),
        new MoveInfo(false,53,140),
        new MoveInfo(true,97,186),
        new MoveInfo(false,40,50),
    };
};