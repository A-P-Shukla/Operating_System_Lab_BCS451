#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>

int data = 0; // Shared data
int readCount = 0; // Number of active readers

// Semaphores
sem_t mutex; // Protects readCount variable
sem_t wmutex; // For writers to have exclusive access

void writer(int value) {
    sem_wait(&wmutex); // Wait for exclusive access
    data = value;
    printf("Writer wrote: %d\n", value);
    sem_post(&wmutex); // Release exclusive access
}

void reader(int id) {
    sem_wait(&mutex); // Protect readCount update
    readCount++;
    if (readCount == 1) {
        sem_wait(&wmutex); // First reader locks writer out
    }
    sem_post(&mutex);
    
    // Critical section: reading
    printf("Reader %d read: %d\n", id, data);
    
    sem_wait(&mutex); // Protect readCount update
    readCount--;
    if (readCount == 0) {
        sem_post(&wmutex); // Last reader allows writers
    }
    sem_post(&mutex);
}

int main() {
    int numwriters, numreaders, i;
    printf("Name: Akhand Pratap Shukla\nRoll No: 2301641540022\n\n");
    
    printf("Enter number of writers: ");
    scanf("%d", &numwriters);
    
    printf("Enter number of readers: ");
    scanf("%d", &numreaders);
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    
    // Create writer processes
    for (i = 0; i < numwriters; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Writer process
            writer(i + 1);
            exit(0);
        }
    }
    
    // Create reader processes
    for (i = 0; i < numreaders; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Reader process
            reader(i + 1);
            exit(0);
        }
    }
    
    // Wait for all child processes
    for (i = 0; i < numwriters + numreaders; i++) {
        wait(NULL);
    }
    
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wmutex);
    
    return 0;
}
