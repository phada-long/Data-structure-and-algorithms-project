#ifndef UNDOSTACK_H       // if this file has not been included before
#define UNDOSTACK_H       // mark it as included (avoid duplicate errors)

#include <iostream>       // for cout (printing to screen)
#include <stack>          // for stack data structure
#include <string>         // for string type
#include "Structures.h"   // Student / Course
#include "LinkedList.h"   // insertStudentEnd, deleteStudentByID, removeCourseByID...
#include "HashTable.h"    // removeCourseHash
#include "Queue.h"        // enqueueRequest, removeFromQueueByID, EnrollmentRequest
using namespace std;      // so we don't have to write std:: every time

// ================= ACTION TYPES =================
// This list tells us what kind of action was done
enum ActionType {
    ADD_STUDENT,      // student was added
    DELETE_STUDENT,   // student was deleted
    UPDATE_GPA,       // GPA was changed
    ADD_COURSE,       // course was added
    QUEUE_ENQUEUE,     // a student was added to the waitlist
    QUEUE_DEQUEUE      // a student was removed from the waitlist
};

// ================= ACTION STRUCT =================
// This struct stores ONE action: what was done + enough real data to REVERSE it.
// (Previously it only stored a display string, so undo() had nothing to work with.)
struct Action {
    ActionType type;
    string data;              // human-readable description, used by showHistory()

    Student studentSnap;      // ADD_STUDENT: only studentID is used (who to remove)
                               // DELETE_STUDENT: full record, so it can be re-inserted
                               // UPDATE_GPA: studentID + OLD gpa, so it can be restored

    Course courseSnap;        // ADD_COURSE: full record, so it can be removed

    EnrollmentRequest queueSnap; // QUEUE_ENQUEUE / QUEUE_DEQUEUE: studentID + courseID

    Action() {}
};

// ================= UNDO STACK =================
class UndoStack {
private:
    stack<Action> history;   // stack that holds all past actions

    // References to the REAL data. undo() needs these to actually change
    // something, not just print a message.
    StudentList* students = nullptr;
    CourseList* courses = nullptr;
    CourseHashTable* courseTable = nullptr;
    WaitQueue* waitQueue = nullptr;

public:
    UndoStack() {}

    // Call this once in main(), right after the lists are created, e.g:
    //   undoStack.bind(studentList, courseList, &courseTable, &waitQueue);
    // (courseTable and waitQueue are value types in this version, so pass
    // their address with &.)
    void bind(StudentList* s, CourseList* c, CourseHashTable* ct, WaitQueue* q) {
        students = s;
        courses = c;
        courseTable = ct;
        waitQueue = q;
    }

    // ---------------- PUSH HELPERS ----------------
    // Call the matching one right after you make the real change, so the
    // Action carries what undo() needs to reverse it.

    void pushAddStudent(const Student& s) {
        Action a;
        a.type = ADD_STUDENT;
        a.studentSnap = s;
        a.data = "ID:" + s.studentID + " Name:" + s.name;
        history.push(a);
    }

    // Call this with the student's data BEFORE you delete them
    void pushDeleteStudent(const Student& deleted) {
        Action a;
        a.type = DELETE_STUDENT;
        a.studentSnap = deleted;
        a.data = "Deleted ID:" + deleted.studentID;
        history.push(a);
    }

    // Call this with the OLD gpa, before overwriting it
    void pushUpdateGPA(const string& id, double oldGpa) {
        Action a;
        a.type = UPDATE_GPA;
        a.studentSnap.studentID = id;
        a.studentSnap.gpa = oldGpa;
        a.data = "ID:" + id + " GPA reverted to " + to_string(oldGpa);
        history.push(a);
    }

    void pushAddCourse(const Course& c) {
        Action a;
        a.type = ADD_COURSE;
        a.courseSnap = c;
        a.data = "Course:" + c.courseID;
        history.push(a);
    }

    void pushQueueEnqueue(const string& sid, const string& cid) {
        Action a;
        a.type = QUEUE_ENQUEUE;
        a.queueSnap.studentID = sid;
        a.queueSnap.courseID = cid;
        a.data = sid + " -> " + cid;
        history.push(a);
    }

    // Call this with the request that was JUST removed from the queue
    void pushQueueDequeue(const string& sid, const string& cid) {
        Action a;
        a.type = QUEUE_DEQUEUE;
        a.queueSnap.studentID = sid;
        a.queueSnap.courseID = cid;
        a.data = "Removed: " + sid + " -> " + cid;
        history.push(a);
    }

    // ---------------- UNDO LAST ACTION ----------------
    // Call this to undo the most recent action
    void undo() {
        // check if there is anything to undo
        if (history.empty()) {
            cout << "No actions to undo.\n";
            return;   // stop the function early
        }

        Action last = history.top();   // look at the top (most recent) action
        history.pop();                 // remove it from the stack

        cout << "\n[UNDO ACTION] ";

        // check what type of action it was, then ACTUALLY reverse it
        switch (last.type) {
        case ADD_STUDENT:
            if (students) deleteStudentByID(students, last.studentSnap.studentID);
            cout << "Removed added student -> " << last.data << endl;
            break;

        case DELETE_STUDENT:
            if (students) insertStudentEnd(students, last.studentSnap);
            cout << "Restored deleted student -> " << last.data << endl;
            break;

        case UPDATE_GPA:
            if (students) updateStudentGPA(students, last.studentSnap.studentID, last.studentSnap.gpa);
            cout << "Reverted GPA change -> " << last.data << endl;
            break;

        case ADD_COURSE:
            if (courses) removeCourseByID(courses, last.courseSnap.courseID);
            if (courseTable) removeCourseHash(*courseTable, last.courseSnap.courseID);
            cout << "Removed added course -> " << last.data << endl;
            break;

        case QUEUE_ENQUEUE:
            if (waitQueue) removeFromQueueByID(*waitQueue, last.queueSnap.studentID, last.queueSnap.courseID);
            cout << "Removed queued request -> " << last.data << endl;
            break;

        case QUEUE_DEQUEUE:
            if (waitQueue) enqueueRequest(*waitQueue, last.queueSnap.studentID, last.queueSnap.courseID);
            cout << "Re-added request to queue -> " << last.data << endl;
            break;

        default:
            cout << "Unknown action\n";
            break;
        }
    }

    // ---------------- SHOW HISTORY ----------------
    // Call this to display all actions from most recent to oldest
    void showHistory() {
        // check if there is any history to show
        if (history.empty()) {
            cout << "No history available.\n";
            return;   // stop the function early
        }

        stack<Action> temp = history;   // copy the stack so we don't destroy the original

        cout << "\n========== ACTION HISTORY ==========\n";

        // loop until the copy is empty
        while (!temp.empty()) {
            Action a = temp.top();   // get the top action
            temp.pop();              // remove it from the copy

            // print the action type as a label
            switch (a.type) {
            case ADD_STUDENT:
                cout << "ADD_STUDENT: ";
                break;
            case DELETE_STUDENT:
                cout << "DELETE_STUDENT: ";
                break;
            case UPDATE_GPA:
                cout << "UPDATE_GPA: ";
                break;
            case ADD_COURSE:
                cout << "ADD_COURSE: ";
                break;
            case QUEUE_ENQUEUE:
                cout << "QUEUE_ENQUEUE: ";
                break;
            case QUEUE_DEQUEUE:
                cout << "QUEUE_DEQUEUE: ";
                break;
            }

            cout << a.data << endl;   // print the stored info for that action
        }

        cout << "====================================\n";
    }
};

#endif   // end of the header guard
