# Scheduling
An implementation of some CPU scheduling algorithm.
* First In First Out (FIFO)
* Round-robin (RR)
* Shortest Job First (SJF)
## Compile
To compile use flag of C++11.

## Usage

The program use a input file that is structured as followed:
In each line is a process that will be ran. A line contains when the process is arriving followed be how much time it will take to execute it.
### Input example
```
0 20
0 10
4 6
4 8
```
There are two processes that will arrive at time 0 and other two on time 4. The first one, its going to take 20 units of time to execute. The second one, its going to take 10 units of time to execute and so forth...
The output is the list of algorithm names followed by the sequenced averages of the return, response and wait time.
### Output example
```
FCFS 30.5 19.5 19.5
SJF 21.5 10.5 10.5
RR 31.5 2 20.5
```