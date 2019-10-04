//
// Created by domin on 9/16/2019.
//

#ifndef PROJECT1_JOB_H
#define PROJECT1_JOB_H

//Job class for the event queue
class Job {
public:

    int event_type;
    int time;
    int job_number;

    Job(int x, int y, int z)
    {
        event_type = x;
        time = y;
        job_number = z;
    }

    void set_type(int type)  {
        event_type = type;
    }
};


#endif //PROJECT1_JOB_H
