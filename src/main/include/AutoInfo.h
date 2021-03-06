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
    std::vector<MoveInfo*> ra = {
        new MoveInfo(false,0,150),
        new MoveInfo(true,23,130),
        new MoveInfo(false,97,242),
        new MoveInfo(true,71,240),
    };

    std::vector<MoveInfo*> rb = {
        new MoveInfo(false,23,170),
        new MoveInfo(true,65,190),
        new MoveInfo(false,95,213),
        new MoveInfo(true,45,229),
    };

    std::vector<MoveInfo*> ba = {
        new MoveInfo(true,23.5,380),
        new MoveInfo(false,94,222),
        new MoveInfo(true,110,150),
        new MoveInfo(false,40,50),
    };

    std::vector<MoveInfo*> bb = {
        new MoveInfo(true,20,381),
        new MoveInfo(false,58,150),
        new MoveInfo(true,96,186),
        new MoveInfo(false,40,41),
    };

    std::vector<MoveInfo*> getPath(int i){
        if(i==0){
            return ra;
        }
        if(i==1){
            return rb;
        }
        if(i==2){
            return ba;
        }
        if(i==3){
            return bb;
        }
    };
};