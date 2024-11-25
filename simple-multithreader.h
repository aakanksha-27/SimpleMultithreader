#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <pthread.h>
#include <cstdlib>

int threadCount;

struct TaskSingle {
    int startIndex;
    int endIndex;
    std::function<void(int)> lambda;
};

struct TaskDouble {
    int startRange1, endRange1;
    int startRange2, endRange2;
    std::function<void(int, int)> lambda;
};

void* run_task_single(void* data) {
    TaskSingle* taskData = static_cast<TaskSingle*>(data);
    for (int i = taskData->startIndex; i < taskData->endIndex; i++) taskData->lambda(i);
    delete taskData;
    return NULL;
}

void parallel_for(int low, int high, std::function<void(int)> &&lambda, int numThreads){
    if (numThreads <= 0) {
        perror("Error: Invalid number of threads");
        exit(1);
    }
    threadCount = numThreads;
    pthread_t threads[threadCount];
    int segment = (high - low) / threadCount;

    if (segment == 0) {
        perror("Error: Too many threads for the given range");
        threadCount = (high - low) > 0 ? (high - low) : 1;
        segment = 1;
    }

    for (int i = 0; i < threadCount; i++) {
        int segmentStart = low + i * segment;
        int segmentEnd = segmentStart + segment;
        if (i == threadCount - 1) segmentEnd = high;

        TaskSingle* taskDetails = new TaskSingle{segmentStart, segmentEnd, lambda};
        int result = pthread_create(&threads[i], NULL, run_task_single, taskDetails);
        if (result != 0) {
            perror("Error: pthread_create failed");
            exit(1);
        }
    }

    for (int i = 0; i < threadCount; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result != 0) {
            perror("Error: pthread_join failed");
            exit(1);
        }
    }
}

void* run_task_double(void* data) {
    TaskDouble* taskData = static_cast<TaskDouble*>(data);
    for (int i = taskData->startRange1; i < taskData->endRange1; i++) {
        for (int j = taskData->startRange2; j < taskData->endRange2; j++) taskData->lambda(i, j);
    }
    delete taskData;
    return NULL;
}

void parallel_for(int low1, int high1, int low2, int high2, std::function<void(int, int)> &&lambda, int numThreads){
    if (numThreads <= 0) {
        perror("Error: Invalid number of threads");
        exit(1);
    }
    threadCount = numThreads;
    pthread_t threads[threadCount];
    int segment1 = (high1 - low1) / threadCount;
    int segment2 = (high2 - low2) / threadCount;

    if (segment1 == 0 || segment2 == 0) {
        perror("Error: Too many threads for the given ranges");
        threadCount = 1;
        segment1 = segment2 = 1;
    }

    for (int i = 0; i < threadCount; i++) {
        int rangeStart1 = low1 + i * segment1;
        int rangeEnd1 = rangeStart1 + segment1;
        if (i == threadCount - 1) {
            rangeEnd1 = high1;
        }

        int rangeStart2 = low2 + i * segment2;
        int rangeEnd2 = rangeStart2 + segment2;
        if (i == threadCount - 1) {
            rangeEnd2 = high2;
        }

        TaskDouble* taskDetails = new TaskDouble{rangeStart1, rangeEnd1, rangeStart2, rangeEnd2, lambda};
        int result = pthread_create(&threads[i], NULL, run_task_double, taskDetails);
        if (result != 0) {
            perror("Error: pthread_create failed");
            exit(1);
        }
    }

    for (int i = 0; i < threadCount; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result != 0) {
            perror("Error: pthread_join failed");
            exit(1);
        }
    }
}
