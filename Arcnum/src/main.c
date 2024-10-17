#include "spark.h"
#include <stdio.h>

#define NUM_TASKS 1000

/* Task function that computes the square of an integer */
SparkHandle SquareFunction(SparkHandle arg) {
    int value = *(int*)arg;
    int* result = (int*)malloc(sizeof(int));
    if (result == NULL) {
        return NULL; // Handle memory allocation failure
    }
    *result = value * value;
#ifdef _WIN32
    printf("Thread %lu: Computed square of %d = %d\n",
        GetCurrentThreadId(), value, *result);
#else
    printf("Thread %lu: Computed square of %d = %d\n",
        (unsigned long)pthread_self(), value, *result);
#endif
    return result;
}


int main() {
    SparkThreadPool pool = SparkCreateThreadPool(4);
    if (pool == NULL) {
        fprintf(stderr, "Failed to create thread pool\n");
        return EXIT_FAILURE;
    }

    SparkTaskHandle tasks[NUM_TASKS];
    int args[NUM_TASKS];
    SparkResult result;

    /* Submit multiple tasks to the thread pool */
    for (int i = 0; i < NUM_TASKS; ++i) {
        args[i] = i + 1; // Arguments from 1 to NUM_TASKS
        tasks[i] = SparkAddTaskThreadPool(pool, SquareFunction, &args[i]);
        
    }

    /* Wait for all tasks to complete and collect results */
    for (int i = 0; i < NUM_TASKS; ++i) {
        result = SparkWaitTask(tasks[i]);
        if (result != SPARK_SUCCESS) {
            fprintf(stderr, "Failed to wait for task %d\n", i);
            continue;
        }

        int* task_result = (int*)tasks[i]->result;
        if (task_result != NULL) {
            printf("Main Thread: Task %d result = %d\n", i, *task_result);
            free(task_result);
        }
        else {
            printf("Main Thread: Task %d failed to compute result\n", i);
        }

        /* Clean up the task */
        SparkTaskDestroy(tasks[i]);
    }

    /* Clean up the thread pool */
    SparkDestroyThreadPool(pool);

    return EXIT_SUCCESS;
}
