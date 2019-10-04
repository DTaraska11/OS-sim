//
// Created by domin on 9/16/2019.
//

#ifndef PROJECT1_DEFINITIONS_H
#define PROJECT1_DEFINITIONS_H

#define CPU_FINISHED 3
#define DISK1_FINISHED 4
#define DISK2_FINISHED 5
#define WORKING_CPU 6
#define WORKING_DISK1 7
#define WORKING_DISK2 8
#define CPU_QUEUE 2
#define DISK1_QUEUE 9
#define DISK2_QUEUE 10
#define ARRIVED 1
#define DONE 11
#define END_SIMULATION -1


bool cpu_busy = false; //tracks if cpu is currently busy
bool disk1_busy = false; //tracks if disk1 is currently busy
bool disk2_busy = false; //tracks if disk2 is currently busy
int vals[12];

int number_of_jobs = 100000; //maximum number of job object to be created on runtime

int jvector_counter = 0; //keeps track of which point in the job vector we are at
int current_time = 0; //tracks the current time
int cpuq_max = 0; //tracks max cpu q length
int disk1q_max = 0; //tracks max disk1 q length
int disk2q_max = 0; //tracks max disk2 q length
double cpuq_sum = 0; //variable for average size calculation
int cpuq_avg_count = 0; //variable for average size calculation
double disk1q_sum = 0; //variable for average size calculation
int disk1q_avg_count = 0; //variable for average size calculation
double disk2q_sum = 0; //variable for average size calculation
int disk2q_avg_count = 0; //variable for average size calculation
double eventq_sum = 0; //variable for average size calculation
int eventq_avg_count = 0; //variable for average size calculation
int jobs_completed = 0; //number of jobs that were completed (don't require further processing)

//many variables for calculating statistics
int cpu_busy_start = 0;
int cpu_busy_end = 0;
int disk1_busy_start = 0;
int disk1_busy_end = 0;
int disk2_busy_start = 0;
int disk2_busy_end = 0;
double disk1_busy_time = 0;
double disk2_busy_time = 0;
double cpu_busy_time = 0;
double cpu_responseTime = 0;
int cpuResponseCount = 0;
double disk1_responseTime = 0;
int disk1ResponseCount = 0;
double disk2_responseTime = 0;
int disk2ResponseCount = 0;
double cpu_maxResponseTime = 0;
double disk1_maxResponseTime = 0;
double disk2_maxResponseTime = 0;
double cpu_responseSum = 0;
double disk1_responseSum = 0;
double disk2_responseSum = 0;
double cpu_jobsCompleted = 0;
double disk1_jobsCompleted = 0;
double disk2_jobsCompleted = 0;



#endif //PROJECT1_DEFINITIONS_H
