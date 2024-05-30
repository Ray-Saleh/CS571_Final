#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to represent a process
struct Process {
    int pid;                // Process ID
    int arrival_time;       // Arrival time of the process
    int priority;           // Priority of the process
    int burst_time;         // CPU burst units required by the process
    int waiting_time;       // Waiting time of the process
    int turnaround_time;    // Turnaround time of the process
    int response_time;      // Response time of the process
    bool completed;         // Flag to indicate if the process has completed
};

// Function prototypes
void fifo_scheduler(vector<Process>& processes);
void sjf_scheduler(vector<Process>& processes);
void priority_scheduler(vector<Process>& processes);
void simulate_scheduler(vector<Process>& processes, void (*scheduler)(vector<Process>&));
void print_statistics(const vector<Process>& processes);

int main() {
    // Vector to store the processes
    vector<Process> processes;
    // Read input file
    ifstream inputFile("input.txt");
    int pid, arrival_time, priority, burst_time;
    while (inputFile >> pid >> arrival_time >> priority >> burst_time) {
        // Add each process to the vector
        processes.push_back({pid, arrival_time, priority, burst_time, 0, 0, -1, false});
    }
    // Choose scheduling algorithm
    cout << "Choose scheduling algorithm:\n";
    cout << "1. FIFO\n";
    cout << "2. SJF without preemption\n";
    cout << "3. Priority with preemption\n";
    int choice;
    cin >> choice;
    // Dispatch scheduler based on user's choice
    switch (choice) {
        case 1:
            simulate_scheduler(processes, fifo_scheduler);
            break;
        case 2:
            simulate_scheduler(processes, sjf_scheduler);
            break;
        case 3:
            simulate_scheduler(processes, priority_scheduler);
            break;
        default:
            cout << "Invalid choice!\n";
            return 1;
    }
    // Print statistics after simulation completes
    print_statistics(processes);
    return 0;
}

// FIFO Scheduling Algorithm
void fifo_scheduler(vector<Process>& processes) {
    int current_time = 0;
    queue<Process> ready_queue;
    int completed_processes = 0;
    // Loop until all processes are completed
    while (completed_processes < processes.size()) {
        // Check for arrived processes
        for (Process& process : processes) {
            if (!process.completed && process.arrival_time <= current_time) {
                ready_queue.push(process);
            }
        }
        // If there are processes in the ready queue
        if (!ready_queue.empty()) {
            Process current_process = ready_queue.front();
            ready_queue.pop();
            // Calculate waiting time, response time, and turnaround time
            current_process.response_time = current_time - current_process.arrival_time;
            current_process.waiting_time = current_time - current_process.arrival_time;
            current_time += current_process.burst_time;
            current_process.turnaround_time = current_time - current_process.arrival_time;
            // Mark process as completed and update in the vector
            current_process.completed = true;
            completed_processes++;
            processes[current_process.pid - 1] = current_process; // Update process in the vector
        } else {
            // If no process is available, proceed to next time unit
            current_time++;
        }
    }
}

// SJF Scheduling Algorithm
void sjf_scheduler(vector<Process>& processes) {
    int current_time = 0;
    int completed_processes = 0;
    // Loop until all processes are completed
    while (completed_processes < processes.size()) {
        int shortest_burst = INT_MAX;
        int shortest_index = -1;
        // Find the process with the shortest burst time
        for (int i = 0; i < processes.size(); ++i) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_index = i;
            }
        }
        // If a process is found
        if (shortest_index != -1) {
            Process& current_process = processes[shortest_index];
            // Calculate waiting time, response time, and turnaround time
            current_process.response_time = current_time - current_process.arrival_time;
            current_process.waiting_time = current_time - current_process.arrival_time;
            current_time += current_process.burst_time;
            current_process.turnaround_time = current_time - current_process.arrival_time;
            // Mark process as completed
            current_process.completed = true;
            completed_processes++;
        } else {
            // If no process is available, proceed to next time unit
            current_time++;
        }
    }
}

// Priority Scheduling Algorithm
void priority_scheduler(vector<Process>& processes) {
    int current_time = 0;
    int completed_processes = 0;
    // Loop until all processes are completed
    while (completed_processes < processes.size()) {
        int highest_priority = INT_MAX;
        int highest_index = -1;
        // Find the process with the highest priority
        for (int i = 0; i < processes.size(); ++i) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_index = i;
            }
        }
        // If a process is found
        if (highest_index != -1) {
            Process& current_process = processes[highest_index];
            // Calculate waiting time, response time, and turnaround time
            current_process.response_time = current_time - current_process.arrival_time;
            current_process.waiting_time = current_time - current_process.arrival_time;
            current_time += current_process.burst_time;
            current_process.turnaround_time = current_time - current_process.arrival_time;
            // Mark process as completed
            current_process.completed = true;
            completed_processes++;
        } else {
            // If no process is available, proceed to next time unit
            current_time++;
        }
    }
}

// Function to simulate scheduler
void simulate_scheduler(vector<Process>& processes, void (*scheduler)(vector<Process>&)) {
    // Call the specified scheduler function
    scheduler(processes);
}

// Function to print simulation statistics
void print_statistics(const vector<Process>& processes) {
    // Variables to store total times and counts
    int total_elapsed_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;
    int total_burst_time = 0;
    int completed_processes = 0;
    
    // Iterate through processes to calculate statistics
    for (const Process& process : processes) {
        if (process.completed) {
            total_elapsed_time = max(total_elapsed_time, process.turnaround_time);
            total_waiting_time += process.waiting_time;
            total_turnaround_time += process.turnaround_time;
            total_response_time += process.response_time;
            total_burst_time += process.burst_time;
            completed_processes++;
        }
    }

    // Calculate statistics
    double throughput = (double)completed_processes / completed_processes; // Total number of processes is same as completed processes
    double cpu_utilization = (double)total_burst_time / total_elapsed_time;
    double avg_waiting_time = (double)total_waiting_time / completed_processes;
    double avg_turnaround_time = (double)total_turnaround_time / completed_processes;
    double avg_response_time = (double)total_response_time / completed_processes;

    // Print statistics to output file
    ofstream outputFile("output.txt");
    outputFile << "Number of processes: " << completed_processes << endl;
    outputFile << "Total elapsed time: " << total_elapsed_time << endl;
    outputFile << "Throughput: " << throughput << endl;
    outputFile << "CPU utilization: " << cpu_utilization << endl;
    outputFile << "Average waiting time: " << avg_waiting_time << endl;
    outputFile << "Average turnaround time: " << avg_turnaround_time << endl;
    outputFile << "Average response time: " << avg_response_time << endl;
    outputFile.close();
}
