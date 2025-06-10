#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>  

typedef struct {
    int worker_id;
    int tasks_completed;
} t_worker;

void* worker_routine(void* arg) {
    t_worker* worker = (t_worker*)arg;
    
    while (worker->tasks_completed < 3) {
        // Job 1
        printf("Worker %d is coding\n", worker->worker_id);
        usleep(1000000); // 1 second
        
        // Job 2
        printf("Worker %d is testing\n", worker->worker_id);
        usleep(500000); // 0.5 seconds
        
        // Job 3
        printf("Worker %d is documenting\n", worker->worker_id);
        usleep(300000); // 0.3 seconds
        
        worker->tasks_completed++;
    }
    return NULL;
}

int main() {
    pthread_t workers[3];
    t_worker worker_data[3];
    
    // Initialize each worker's data
    for (int i = 0; i < 3; i++) {
        worker_data[i].worker_id = i;
        worker_data[i].tasks_completed = 0;
    }
    
    // Create worker threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&workers[i], NULL, worker_routine, &worker_data[i]);
    }
    
    // Wait for all workers to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(workers[i], NULL);
    }
    
    return 0;
}