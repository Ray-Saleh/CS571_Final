# Producer-Consumer Problem

This project implements the Producer-Consumer problem in C++ using pthreads library for multi-threading. The Producer-Consumer problem is a classic synchronization problem where there are producers that generate data and put it into a shared buffer, and consumers that take data from the buffer and process it.

## Compilation and Execution

To compile the program, make sure you have a C++ compiler installed. You can compile the source code using the following command:

```bash```
g++ -o producer_consumer producer_consumer.cpp -lpthread


To run the program, use the following command:

./producer_consumer <num_producers> <num_consumers> <sleep_time>
<num_producers>: Number of producer threads to create.
<num_consumers>: Number of consumer threads to create.
<sleep_time>: Duration (in seconds) for which the program should run before terminating.


example ./producer_consumer 2 3 5