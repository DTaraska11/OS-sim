Dominic Taraska
Project 1


The following documentation provides some explanation for the specific mechanisms that I decided to implement 
in order to complete the simulator, as well as some of my reasoning or thought processes throughout the course of 
solving specific problems. This documentation is roughly chronological with regard to the order that each 
specific component of my program was implemented. 
 
Reading from config file:  


This part was relatively straight-forward and something that I’ve had to do many times before for assignments/projects. I declared 
the variables in my program and made a function that parses the text file and reads the correct values 
into an array. The array is then moved into my main method where the values are stored in their appropriate variables. 


Randomness: 


Randomness in my program is simulated using a combination of a SEED, srand(), and rand(). 
This is relevant for generating times associated with the finishing of job services at components and 
also interarrival time for job creation. 



Jobs: 


        I decided to implement jobs in my program in the form of a Job class. This class has a constructor 
that takes multiple arguments that set time, event type, and the job number. Job number is a constant variable 
(as it will never change) and the associated time and event type change accordingly throughout the course of the simulation. 


Event Queue:


        In order to create an event queue, I decided to implement the priority_queue() functionality 
from the <queue> library. The event queue is of type <Job>. I made my own custom comparison function that is 
used to sort the queue by each Job’s (or “event’s”)  associated time. 


Server FIFO Queues: 


        To create the server queues for the CPU and disks, I used the queue() functionality, also from the 
<queue> library. The servers know when to begin servicing the next job because of various boolean variables 
that signal when the CPU/Disks are busy. Once a job finishes being served, the value is set to false. When a job 
begins being serviced, the value is set to true.





Statistic Gathering/Logging: 
        
My program prints out the necessary information as the program is running. 
This includes the time, the type of event, and the job number associated with it. At the end 
of the program it also calculates and prints out the required statistical data. Most of this is
 calculated after the program has run its course, but there are some intermediary steps taken during the 
simulation loop that enable the program to perform those calculations later on; things such as 
keeping track of certain max values, or keeping track of how long a certain component has been servicing a job, etc.




In a maximum time of 10000 units my program processes over 1000 jobs, as instructed. It also remains fairly consistent 
upon changing the SEED for the random generator. 


The biggest issue with this assignment was making sure that the timing of every step was perfect, like making 
sure that I increment the system time in the right places or handling certain events in the right loops. 
I also could have put more of the event handlers in their own functions, but I simply ran out of time at the end.

I tested my program with 11 different configurations and put my results into a table called RUNS.jpg.
I tried saving it as a plain text file after creating it in excel but that messed up the formating pretty badly, so I
attached an image of it instead. 