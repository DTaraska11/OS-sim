#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Job.h"
#include "compare_time.h"
#include "read_config.h"
#include "definitions.h"
#include <queue>
#include <vector>
#include <random>
#include <iostream>

//driver function
int main()
{

    int *config_vars = read_config();
    const int INIT_TIME = config_vars[0];
    const int FIN_TIME = config_vars[1];
    const int ARRIVE_MIN = config_vars[2];
    const int ARRIVE_MAX = config_vars[3];
    const int QUIT_PROB = config_vars[4];
    const int CPU_MIN = config_vars[5];
    const int CPU_MAX = config_vars[6];
    const int DISK1_MIN = config_vars[7];
    const int DISK1_MAX = config_vars[8];
    const int DISK2_MIN = config_vars[9];
    const int DISK2_MAX = config_vars[10];
    const int SEED = config_vars[11];
    printf("INIT_TIME: %d \n", INIT_TIME);
    printf("FIN_TIME: %d \n", FIN_TIME);
    printf("ARRIVE_MIN: %d \n", ARRIVE_MIN);
    printf("ARRIVE_MAX: %d \n", ARRIVE_MAX);
    printf("QUIT PROB: %d \n", QUIT_PROB);
    printf("CPI_MIN: %d \n", CPU_MIN);
    printf("CPU_MAX: %d \n", CPU_MAX);
    printf("DISK1_MIN: %d \n", DISK1_MIN);
    printf("DISK1_MAX: %d \n", DISK1_MAX);
    printf("DISK2_MIN: %d \n", DISK2_MIN);
    printf("DISK2_MAX: %d \n", DISK2_MAX);
    printf("SEED: %d \n", SEED);





    bool simulation_finished = false;

    std::priority_queue <Job, std::vector<Job>, compare_time> event_queue; //minheap event queue
    std::queue<Job> cpu_queue; //CPU FIFO queue
    std::queue<Job> disk1_queue; //Disk1 FIFO queue
    std::queue<Job> disk2_queue; //Disk2 FIFO queue
    //creates job objects on runtime
    std::vector<Job> job_objects;

    for(int x = 0; x < number_of_jobs; x++)
    {
        job_objects.emplace_back(1,INIT_TIME,(x+1));
    }

    //creates the final "job" which actually just signals the end of the simulation. Not actually a job. Pushes it onto the event queue.
    Job end_of_simulation(END_SIMULATION, FIN_TIME, -1);
    event_queue.push(end_of_simulation);
    event_queue.push(job_objects[jvector_counter]); // adds the first job to event queue

    srand(SEED); //seeds random generator


    //loop to simulate system

    while(!simulation_finished && !event_queue.empty())
    {


        if (!event_queue.empty() && event_queue.top().event_type == ARRIVED) //if top event has just arrived
        {
            current_time = event_queue.top().time;


            printf("Job%d has just arrived at time %d \n", event_queue.top().job_number, current_time);


            cpu_queue.push(event_queue.top()); //add it to cpu queue

            job_objects[(event_queue.top().job_number)-1].set_type(CPU_QUEUE);
            printf("Job%d has been added to cpu queue at time %d \n", event_queue.top().job_number, current_time);


            event_queue.pop(); //removes from event queue

            //creates next job and sends to event q

            job_objects[jvector_counter+1].time = current_time + (ARRIVE_MIN + (std::rand() % ( ARRIVE_MAX - ARRIVE_MIN + 1 ) ));
            event_queue.push(job_objects[jvector_counter+1]);
            printf("Job%d has been created at time %d \n", job_objects[jvector_counter+1].job_number, current_time);
            jvector_counter++;



            //statistic gathering
            if(cpu_queue.size() > cpuq_max)
            {
                cpuq_max = cpu_queue.size();
            }
            cpuq_avg_count++;
            cpuq_sum = cpuq_sum + cpu_queue.size();

            eventq_avg_count++;
            eventq_sum = eventq_sum + event_queue.size();


        }
        else if (!event_queue.empty() && event_queue.top().event_type == CPU_FINISHED) // if top event has just finished with CPU
        {

            printf("Job%d has just finished at the cpu \n", event_queue.top().job_number);
            cpu_jobsCompleted++;
            cpu_busy = false;
            cpu_busy_end = current_time;
            cpu_busy_time = cpu_busy_time + (cpu_busy_end - cpu_busy_start);
            cpu_responseTime = cpu_busy_end - cpu_busy_start;
            cpu_responseSum = cpu_responseSum + cpu_responseTime;
            cpuResponseCount++;
            if(cpu_responseTime > cpu_maxResponseTime)
            {
                cpu_maxResponseTime = cpu_responseTime;
            }
            if(((1 + std::rand() % (100 - 1 + 1))) <= QUIT_PROB) // if job is done (doesnt need to use disk)
            {
                job_objects[(event_queue.top().job_number)-1].set_type(DONE); //set event status to 'DONE'
                current_time = event_queue.top().time;

                printf("Job%d has just completed at time %d \n", event_queue.top().job_number, current_time);
                jobs_completed++;

                event_queue.pop();
                eventq_avg_count++;
                eventq_sum = eventq_sum + event_queue.size();

            }

            else{ // job needs to use disk

                //comparing disk queue sizes to see which is smallest
                if (disk1_queue.size() < disk2_queue.size())
                {
                    job_objects[(event_queue.top().job_number)-1].set_type(DISK1_QUEUE);
                    disk1_queue.push(event_queue.top());
                    current_time = event_queue.top().time;
                    printf("Job%d has been added to disk1 queue at time %d\n", event_queue.top().job_number, current_time);
                    event_queue.pop();
                }
                else if (disk1_queue.size() > disk2_queue.size())
                {
                    job_objects[(event_queue.top().job_number)-1].set_type(DISK2_QUEUE);
                    disk2_queue.push(event_queue.top());
                    current_time = event_queue.top().time;
                    printf("Job%d has been added to disk2 queue at time %d \n", event_queue.top().job_number, current_time);
                    event_queue.pop();
                }
                //picks random queue if both are of same length
                else
                {
                    if((1 + (std::rand() % ( 2 - 1 + 1 ) )) == 1 )
                    {
                        job_objects[(event_queue.top().job_number)-1].set_type(DISK1_QUEUE);
                        disk1_queue.push(event_queue.top());
                        current_time = event_queue.top().time;
                        printf("Job%d has been added to disk1 queue at time %d \n ", event_queue.top().job_number, current_time);
                        event_queue.pop();

                    }
                    else
                    {
                        job_objects[(event_queue.top().job_number)-1].set_type(DISK2_QUEUE);
                        disk2_queue.push(event_queue.top());
                        current_time = event_queue.top().time;
                        printf("Job%d has been added to disk2 queue at time %d \n", event_queue.top().job_number, current_time);
                        event_queue.pop();


                    }
                }
                //statistic gathering
                if (disk1_queue.size() > disk1q_max)
                {
                    disk1q_max = disk1_queue.size();
                }
                disk1q_avg_count++;
                disk1q_sum = disk1q_sum + disk1_queue.size();
                if (disk2_queue.size() > disk2q_max)
                {
                    disk2q_max = disk2_queue.size();
                }
                disk2q_avg_count++;
                disk2q_sum = disk2q_sum + disk2_queue.size();


            }

            //statistic gathering
            if (disk1_queue.size() > disk1q_max)
            {
                disk1q_max = disk1_queue.size();
            }
            disk1q_avg_count++;
            disk1q_sum = disk1q_sum + disk1_queue.size();
            if (disk2_queue.size() > disk2q_max)
            {
                disk2q_max = disk2_queue.size();
            }
            disk2q_avg_count++;
            disk2q_sum = disk2q_sum + disk2_queue.size();

            eventq_avg_count++;
            eventq_sum = eventq_sum + event_queue.size();


        }
        //handles job finishing at either disk
        else if (!event_queue.empty() && event_queue.top().event_type == DISK1_FINISHED)
        {
            current_time = event_queue.top().time;
            disk1_busy = false; //disk is no longer busy
            disk1_jobsCompleted++;


            disk1_busy_end = current_time;
            disk1_busy_time = disk1_busy_time + (disk1_busy_end - disk1_busy_start);
            disk1_responseTime = disk1_busy_end - disk1_busy_start;
            disk1_responseSum = disk1_responseSum + disk1_responseTime;
            disk1ResponseCount++;
            if(disk1_responseTime > disk1_maxResponseTime)
            {
                disk1_maxResponseTime = disk1_responseTime;
            }




            printf("Job%d has just finished at disk1 at time %d \n", event_queue.top().job_number, current_time);
            job_objects[(event_queue.top().job_number)-1].set_type(CPU_QUEUE);
            cpu_queue.push(job_objects[(event_queue.top().job_number)-1]);
            printf("Job%d has just arrived at the cpu queue at time %d \n", event_queue.top().job_number, current_time);

            event_queue.pop();


            //statistic gathering
            if (disk1_queue.size() > disk1q_max)
            {
                disk1q_max = disk1_queue.size();
            }
            disk1q_avg_count++;
            disk1q_sum = disk1q_sum + disk1_queue.size();
            if (disk2_queue.size() > disk2q_max)
            {
                disk2q_max = disk2_queue.size();
            }
            disk2q_avg_count++;
            disk2q_sum = disk2q_sum + disk2_queue.size();

            if(cpu_queue.size() > cpuq_max)
            {
                cpuq_max = cpu_queue.size();
            }
            cpuq_avg_count++;
            cpuq_sum = cpuq_sum + cpu_queue.size();

            eventq_avg_count++;
            eventq_sum = eventq_sum + event_queue.size();



        }
        else if (!event_queue.empty() && event_queue.top().event_type == DISK2_FINISHED) //handles disk finishing
        {

            current_time = event_queue.top().time;
            disk2_busy = false;
            disk2_jobsCompleted++;
            disk2_busy_end = current_time;
            disk2_busy_time = disk2_busy_time + (disk2_busy_end - disk2_busy_start);
            disk2_responseTime = disk2_busy_end - disk2_busy_start;
            disk2_responseSum = disk2_responseSum + disk2_responseTime;
            disk2ResponseCount++;
            if(disk2_responseTime > disk2_maxResponseTime)
            {
                disk2_maxResponseTime = disk2_responseTime;
            }

            printf("Job%d has just finished at disk2 at time %d  \n", event_queue.top().job_number, current_time);
            job_objects[(event_queue.top().job_number)-1].set_type(CPU_QUEUE);
            cpu_queue.push(job_objects[(event_queue.top().job_number)-1]);
            printf("Job%d has just arrived at the cpu queue at time %d \n", event_queue.top().job_number, current_time);


            event_queue.pop();

            //statistic gathering
            if (disk1_queue.size() > disk1q_max)
            {
                disk1q_max = disk1_queue.size();
            }
            disk1q_avg_count++;
            disk1q_sum = disk1q_sum + disk1_queue.size();
            if (disk2_queue.size() > disk2q_max)
            {
                disk2q_max = disk2_queue.size();
            }
            disk2q_avg_count++;
            disk2q_sum = disk2q_sum + disk2_queue.size();

            if(cpu_queue.size() > cpuq_max)
            {
                cpuq_max = cpu_queue.size();
            }
            cpuq_avg_count++;
            cpuq_sum = cpuq_sum + cpu_queue.size();

            eventq_avg_count++;
            eventq_sum = eventq_sum + event_queue.size();

        }


        //if simulation is over
        else if(event_queue.top().event_type == END_SIMULATION)
        {


            printf("SIMULATION COMPLETE \n");
            printf("------------------------------------------------------------------------------------- \n");
            printf("\n \n \n");
            simulation_finished = true;
        }

        //-----------------------------------------------------------------------

        //if cpu is idle and there are jobs waiting in queue
        if(!cpu_queue.empty() && !cpu_busy)
        {

            cpu_queue.front().set_type(CPU_FINISHED);
            cpu_queue.front().time = current_time + ((CPU_MIN + std::rand() % (CPU_MAX - CPU_MIN + 1)));
            printf("Job%d began at cpu at time %d \n", cpu_queue.front().job_number, current_time);

            event_queue.push(cpu_queue.front());
            cpu_queue.pop();


            cpu_busy = true;
            cpu_busy_start = current_time;




        }
        //if disk1 is idle and there are jobs waiting in queue
        if(!disk1_queue.empty() && !disk1_busy)
        {

            //pushes next job in queue to the disk, creates the disk finished event
            disk1_queue.front().set_type(DISK1_FINISHED);
            disk1_queue.front().time = current_time + ((DISK1_MIN + std::rand() % (DISK1_MAX - DISK1_MIN + 1)));
            printf("Job%d began at disk1 at time %d \n", disk1_queue.front().job_number, current_time);
            event_queue.push(disk1_queue.front());
            disk1_queue.pop();
            disk1_busy = true;
            disk1_busy_start = current_time;


        }
        //if disk2 is idle and there are jobs waiting in queue
        if(!disk2_queue.empty() && !disk2_busy)
        {

            //pushes next job in queue to the disk, creates the disk finished event
            disk2_queue.front().set_type(DISK2_FINISHED);
            disk2_queue.front().time = current_time + ((DISK2_MIN + std::rand() % (DISK2_MAX - DISK2_MIN + 1)));
            printf("Job%d began at disk2 at time %d \n", disk2_queue.front().job_number, current_time);
            event_queue.push(disk2_queue.front());
            disk2_queue.pop();
            disk2_busy = true;
            disk2_busy_start = current_time;

        }




    }
    //statistic calculating
    double cpu_queue_average_length = cpuq_sum/cpuq_avg_count;
    double disk1_queue_average_length = disk1q_sum/disk1q_avg_count;
    double disk2_queue_average_length = disk2q_sum/disk2q_avg_count;
    double event_queue_average_length = eventq_sum/eventq_avg_count;
    double cpu_utilization = cpu_busy_time/(FIN_TIME - INIT_TIME);
    double disk1_utilization = disk1_busy_time/(FIN_TIME - INIT_TIME);
    double disk2_utilization = disk2_busy_time/(FIN_TIME - INIT_TIME);
    double cpu_avgResponse = cpu_responseSum/cpuResponseCount;
    double disk1_avgResponse = disk1_responseSum/disk1ResponseCount;
    double disk2_avgResponse = disk2_responseSum/disk2ResponseCount;
    double cpu_throughput = cpu_jobsCompleted/(FIN_TIME-INIT_TIME);
    double disk1_throughput = disk1_jobsCompleted/(FIN_TIME-INIT_TIME);
    double disk2_throughput = disk2_jobsCompleted/(FIN_TIME-INIT_TIME);




    printf("     (STATISTICS): \n");
    printf("      ---------- \n");

    printf("cpu queue average length: %lf \n", cpu_queue_average_length);
    printf("disk1 queue average length: %lf \n", disk1_queue_average_length);
    printf("disk2 queue average length: %lf \n", disk2_queue_average_length);
    printf("event queue average length: %lf \n", event_queue_average_length);
    printf("-------------------------------------------------- \n");
    printf("cpu queue max length: %d \n", cpuq_max);
    printf("disk1 queue max length: %d \n", disk1q_max);
    printf("disk2 queue max length: %d \n", disk2q_max);
    printf("-------------------------------------------------- \n");
    printf("cpu utilization: %lf \n", cpu_utilization);
    printf("disk1 utilization: %lf \n", disk1_utilization);
    printf("disk2 utilization: %lf \n", disk2_utilization);
    printf("-------------------------------------------------- \n");
    printf("cpu average response time: %lf \n", cpu_avgResponse);
    printf("disk1 average response time: %lf \n", disk1_avgResponse);
    printf("disk2 average response time: %lf \n", disk2_avgResponse);
    printf("-------------------------------------------------- \n");
    printf("cpu max response time: %lf \n", cpu_maxResponseTime);
    printf("disk1 max response time: %lf \n", disk1_maxResponseTime);
    printf("disk2 max response time: %lf \n", disk2_maxResponseTime);
    printf("-------------------------------------------------- \n");
    printf("cpu throughput: %lf \n", cpu_throughput);
    printf("disk1 throughput: %lf \n", disk1_throughput);
    printf("disk2 throughput: %lf \n", disk2_throughput);
    printf("--------------------------------------------------------- \n");








}




