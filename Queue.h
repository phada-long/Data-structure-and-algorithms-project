<<<<<<< HEAD
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

inline bool dequeueRequest(WaitQueue* q, EnrollmentRequest& request) {
    if (isWaitQueueEmpty(q)) {
        return false;
    }

    request = q->Q[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return true;
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

#endif
=======
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

inline bool dequeueRequest(WaitQueue* q, EnrollmentRequest& request) {
    if (isWaitQueueEmpty(q)) {
        return false;
    }

    request = q->Q[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return true;
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

#endif
>>>>>>> 73a84c83f1336b09682f5c7eb3f11f8df0857738
