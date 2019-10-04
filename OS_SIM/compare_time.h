//
// Created by domin on 9/16/2019.
//

#ifndef PROJECT1_COMPARE_TIME_H
#define PROJECT1_COMPARE_TIME_H


#include "Job.h"
//comparison mechanism for event queue sorting
class compare_time {
public:
    bool operator()(Job& j1, Job& j2){
        if (j1.time > j2.time) return true; //compares two event's associated times
        return false;
    }

};


#endif //PROJECT1_COMPARE_TIME_H
