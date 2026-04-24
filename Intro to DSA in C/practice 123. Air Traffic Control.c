#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 5      // Max planes waiting
#define TOTAL_TIME 100        // Simulation time in units

typedef struct Queue {
    int items[MAX_QUEUE_SIZE];
    int front, rear, count;
} Queue;

void initializeQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFull(Queue *q) {
    return q->count == MAX_QUEUE_SIZE;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

void enqueue(Queue *q, int plane) {
    if (!isFull(q)) {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->items[q->rear] = plane;
        q->count++;
    }
}

int dequeue(Queue *q) {
    if (!isEmpty(q)) {
        int plane = q->items[q->front];
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        q->count--;
        return plane;
    }
    return -1;
}

int main() {
    Queue landingQueue, takeoffQueue;
    initializeQueue(&landingQueue);
    initializeQueue(&takeoffQueue);

    int planesProcessed = 0, landed = 0, tookOff = 0, refused = 0;
    int landingWaitTime = 0, takeoffWaitTime = 0, idleTime = 0;

    srand(time(0));

    for (int time = 0; time < TOTAL_TIME; time++) {
        printf("Time unit: %d\n", time);

        int incomingLanding = rand() % 2;
        int incomingTakeoff = rand() % 2;

        if (incomingLanding) {
            if (!isFull(&landingQueue)) {
                enqueue(&landingQueue, time);
                printf("Plane added to landing queue at time %d.\n", time);
            } else {
                refused++;
                printf("Landing plane refused at time %d.\n", time);
            }
        }

        if (incomingTakeoff) {
            if (!isFull(&takeoffQueue)) {
                enqueue(&takeoffQueue, time);
                printf("Plane added to takeoff queue at time %d.\n", time);
            } else {
                refused++;
                printf("Takeoff plane refused at time %d.\n", time);
            }
        }

        if (!isEmpty(&landingQueue)) {
            int landingTime = dequeue(&landingQueue);
            landingWaitTime += time - landingTime;
            printf("Plane landed that arrived at time %d. Waited %d units.\n", landingTime, time - landingTime);
            landed++;
        } else if (!isEmpty(&takeoffQueue)) {
            int takeoffTime = dequeue(&takeoffQueue);
            takeoffWaitTime += time - takeoffTime;
            printf("Plane took off that queued at time %d. Waited %d units.\n", takeoffTime, time - takeoffTime);
            tookOff++;
        } else {
            printf("Runway is idle.\n");
            idleTime++;
        }
    }

    planesProcessed = landed + tookOff + refused;
    printf("\nSimulation Report:\n");
    printf("Total planes processed: %d\n", planesProcessed);
    printf("Planes landed: %d\n", landed);
    printf("Planes took off: %d\n", tookOff);
    printf("Planes refused: %d\n", refused);
    printf("Average landing wait time: %.2f units\n", (landed ? (float)landingWaitTime / landed : 0));
    printf("Average takeoff wait time: %.2f units\n", (tookOff ? (float)takeoffWaitTime / tookOff : 0));
    printf("Runway idle time: %d units\n", idleTime);
    printf("Percentage of runway idle time: %.2f%%\n", ((float)idleTime / TOTAL_TIME) * 100);

    return 0;
}
