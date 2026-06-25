#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

const int WAIT_QUEUE_SIZE = 10;

struct EnrollmentRequest {
    std::string studentID;
    std::string courseID;
};

struct WaitQueue {
    int front;
    int rear;
    EnrollmentRequest Q[WAIT_QUEUE_SIZE];
};

inline WaitQueue* createWaitQueue() {
    WaitQueue* q = new WaitQueue();
    q->front = -1;
    q->rear = -1;
    return q;
}

inline bool isWaitQueueEmpty(WaitQueue* q) {
    return q->front == -1 || q->front > q->rear;
}

inline bool isWaitQueueFull(WaitQueue* q) {
    return q->rear == WAIT_QUEUE_SIZE - 1;
}

inline void enqueueRequest(WaitQueue* q, const std::string& studentID, const std::string& courseID) {
    if (isWaitQueueFull(q)) {
        std::cout << "Cannot enqueue request. Wait queue is full\n";
        return;
    }

    EnrollmentRequest request;
    request.studentID = studentID;
    request.courseID = courseID;

    if (isWaitQueueEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear++;
    }

    q->Q[q->rear] = request;
}

inline void displayWaitQueue(WaitQueue* q) {
    if (isWaitQueueEmpty(q)) {
        std::cout << "No waiting students in queue.\n";
        return;
    }

    std::cout << "Waiting students:\n";
    for (int i = q->front; i <= q->rear; i++) {
        std::cout << "  Student ID: " << q->Q[i].studentID
                  << " | Course ID: " << q->Q[i].courseID << "\n";
    }
}

inline void clearWaitQueue(WaitQueue* q) {
    q->front = -1;
    q->rear = -1;
}

inline bool removeFromQueueByID(WaitQueue* q, const std::string& studentID, const std::string& courseID) {
    if (isWaitQueueEmpty(q)) {
        return false;
    }

    // Find the request to remove
    int removeIndex = -1;
    for (int i = q->front; i <= q->rear; i++) {
        if (q->Q[i].studentID == studentID && q->Q[i].courseID == courseID) {
            removeIndex = i;
            break;
        }
    }

    // If not found, return false
    if (removeIndex == -1) {
        return false;
    }

    // Shift elements after the removed index
    for (int i = removeIndex; i < q->rear; i++) {
        q->Q[i] = q->Q[i + 1];
    }

    // Update rear pointer
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->rear--;
    }

    return true;
}

#endif
