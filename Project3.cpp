#include <iostream>  
#include <thread>
#include <semaphore>

using namespace std;

// Define size of shared array
#define MAX_SIZE 100    

// Global shared array 
int buffer[MAX_SIZE];

// Semaphores for synchronization
sem_t wrt;
sem_t mutex;

// Track number of active readers
int readCount = 0;

// Writer thread function
void writer() {

    // Continuous loop
    while (true) {

        // Wait on write semaphore 
        sem_wait(&wrt);

        // Critical section - exclusive access
        // Write to shared array
        for (int i = 0; i < MAX_SIZE; i++) {
            buffer[i] = i;
        }

        // End of critical section
        sem_post(&wrt);
    }
}

// Reader thread function 
void reader() {

    // Continuous loop
    while (true) {

        // Lock access for upcoming read operation
        sem_wait(&mutex);

        // Increment reader count
        readCount++;

        // First reader acquires write lock
        if (readCount == 1) {
            sem_wait(&wrt);
        }

        // Release lock    
        sem_post(&mutex);

        // Critical section - concurrent read access
        // Read from shared array
        for (int i = 0; i < MAX_SIZE; i++) {
            cout << buffer[i] << endl;
        }

        // End of critical section

        // Lock access for completed read operation
        sem_wait(&mutex);

        // Decrement reader count
        readCount--;

        // Last reader releases write lock 
        if (readCount == 0) {
            sem_post(&wrt);
        }

        // Release lock
        sem_post(&mutex);
    }
}

int main() {

    // Initialize semaphores
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    int numReaders, numWriters;

    // Take reader and writer counts
    cout << "Enter number of readers and writers: ";
    cin >> numReaders >> numWriters;

    // Create reader threads
    thread readers[numReaders];
    for (int i = 0; i < numReaders; i++) {
        readers[i] = thread(reader);
    }

    // Create writer threads
    thread writers[numWriters];
    for (int i = 0; i < numWriters; i++) {
        writers[i] = thread(writer);
    }

    // Join all threads
    for (int i = 0; i < numReaders; i++) {
        readers[i].join();
    }
    for (int i = 0; i < numWriters; i++) {
        writers[i].join();
    }

    // Destroy semaphores  
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
//please make sure that you're using c++ v20 to be able to run the code, thank you :)