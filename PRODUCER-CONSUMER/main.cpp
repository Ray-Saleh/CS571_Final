#include <iostream>
#include <fstream> // For file output
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <atomic> // For std::atomic_bool

using namespace std;

#define BUFFER_SIZE 10

mutex mtx;
condition_variable cond_prod, cond_cons;

queue<int> buffer;

atomic_bool running(true); // Flag to control program execution

void producer(int id, ofstream& output) {
    while (running) {
        int item = rand() % 100; // generate random item

        {
            unique_lock<mutex> lock(mtx);
            if (!running) break; // Exit loop if program should terminate
            cond_prod.wait(lock, []{ return buffer.size() < BUFFER_SIZE || !running; });
            if (!running) break; // Exit loop if program should terminate
            
            buffer.push(item);
            output << "Producer " << id << " produced: " << item << endl;
        }
        
        cond_cons.notify_all();
    }
}

void consumer(int id, ofstream& output) {
    while (running) {
        {
            unique_lock<mutex> lock(mtx);
            if (!running) break; // Exit loop if program should terminate
            cond_cons.wait(lock, []{ return !buffer.empty() || !running; });
            if (!running) break; // Exit loop if program should terminate

            int item = buffer.front();
            buffer.pop();
            output << "Consumer " << id << " consumed: " << item << endl;
        }
        
        cond_prod.notify_all();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <num_producers> <num_consumers> <run_time>" << endl;
        return 1;
    }

    int num_producers = atoi(argv[1]);
    int num_consumers = atoi(argv[2]);
    int run_time = atoi(argv[3]);

    // Open output file
    ofstream output("output.txt");
    if (!output) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    vector<thread> producer_threads(num_producers);
    vector<thread> consumer_threads(num_consumers);

    // Create producer threads
    for (int i = 0; i < num_producers; ++i) {
        producer_threads[i] = thread(producer, i, ref(output));
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; ++i) {
        consumer_threads[i] = thread(consumer, i, ref(output));
    }

    // Sleep for specified time
    this_thread::sleep_for(chrono::seconds(run_time));

    // Set the flag to terminate the program
    running = false;

    // Notify all threads to exit
    cond_prod.notify_all();
    cond_cons.notify_all();

    // Join all threads
    for (int i = 0; i < num_producers; ++i) {
        producer_threads[i].join();
    }
    for (int i = 0; i < num_consumers; ++i) {
        consumer_threads[i].join();
    }

    // Close output file
    output.close();

    return 0;
}
