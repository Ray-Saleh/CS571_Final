# CPU Scheduler Simulation

This project simulates a CPU scheduler with three scheduling algorithms: FIFO, SJF without preemption, and Priority with preemption.

## Input
The input data for the simulation is provided in the `input.txt` file. Each line of the file represents a simulated process and contains four integers separated by spaces:
- Process ID
- Arrival time
- Priority
- CPU burst units

For example:
1 0 3 10
2 1 2 5
3 2 1 8
4 3 3 6

This input represents four processes with IDs 1 to 4, arriving at times 0, 1, 2, and 3, respectively. They have priorities 3, 2, 1, and 3, and require CPU burst units of 10, 5, 8, and 6, respectively.

## Output
The simulation statistics are printed to the `output.txt` file after the simulation completes. The statistics include:
- Number of processes: Total number of processes that completed CPU execution.
- Total elapsed time: Total simulated time from the initiation to termination of all processes.
- Throughput: Number of processes executed in one unit of CPU burst time.
- CPU utilization: Percentage of time the CPU is performing work.
- Average waiting time: Average waiting time of all processes.
- Average turnaround time: Average turnaround time of all processes.
- Average response time: Average response time of all processes.

Here's an example output:
Number of processes: 4
Total elapsed time: 26
Throughput: 0.137931
CPU utilization: 1.11538
Average waiting time: 10.5
Average turnaround time: 17.75
Average response time: 10.5


## Running the Program
1. Create or update the `input.txt` file with the simulated processes data.
2. Compile the `scheduler.cpp` file using a C++ compiler.
    ```
    g++ scheduler.cpp -o scheduler
    ```
3. Run the compiled executable.
    ```
    ./scheduler
    ```
4. Choose the desired scheduling algorithm when prompted (1 for FIFO, 2 for SJF, or 3 for Priority).
5. View the output statistics printed to the console and written to the `output.txt` file.

Feel free to modify the `input.txt` file to simulate different scenarios and observe how the CPU scheduler behaves with various inputs.
