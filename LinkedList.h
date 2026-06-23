#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Structures.h"

// =========================================================
// COURSE LINKED LIST OPERATIONS
// =========================================================

inline CourseList* createCourseList() {
    CourseList* ls = new CourseList();
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

inline void insertCourseEnd(CourseList* ls, Course d) {
    CourseElement* E = new CourseElement();
    E->data = d;
    E->next = nullptr;
    if (ls->n == 0) {
        ls->head = E;
    } else {
        ls->tail->next = E;
    }
    ls->tail = E;
    ls->n = ls->n + 1;
}

inline CourseElement* searchCourseByID(CourseList* ls, std::string targetID) {
    CourseElement* curr = ls->head;
    while (curr != nullptr) {
        if (curr->data.courseID == targetID) return curr;
        curr = curr->next;
    }
    return nullptr;
}

inline void displayCourses(CourseList* ls) {
    if (ls->n == 0) {
        std::cout << "No courses found in the system.\n";
        return;
    }
    CourseElement* curr = ls->head;
    while (curr != nullptr) {
        std::cout << "[Course ID: " << curr->data.courseID 
                  << "] Name: " << curr->data.courseName 
                  << " | Credits: " << curr->data.credits << "\n";
        curr = curr->next;
    }
}

// =========================================================
// STUDENT LINKED LIST OPERATIONS
// =========================================================

inline StudentList* createStudentList() {
    StudentList* ls = new StudentList();
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

inline void insertStudentEnd(StudentList* ls, Student d) {
    StudentElement* E = new StudentElement();
    E->data = d;
    E->next = nullptr;
    if (ls->n == 0) {
        ls->head = E;
    } else {
        ls->tail->next = E;
    }
    ls->tail = E;
    ls->n = ls->n + 1;
}

inline StudentElement* searchStudentByID(StudentList* ls, std::string targetID) {
    StudentElement* curr = ls->head;
    while (curr != nullptr) {
        if (curr->data.studentID == targetID) return curr;
        curr = curr->next;
    }
    return nullptr;
}

// Updates an entry directly inside the matched address
inline bool updateStudentGPA(StudentList* ls, std::string id, double newGpa) {
    StudentElement* match = searchStudentByID(ls, id);
    if (match != nullptr) {
        match->data.gpa = newGpa;
        return true;
    }
    return false;
}

// Deletes by ID targeting middle, head, or tail positions
inline void deleteStudentByID(StudentList* ls, std::string id) {
    if (ls->n == 0) return;

    StudentElement* curr = ls->head;
    StudentElement* prev = nullptr;

    while (curr != nullptr) {
        if (curr->data.studentID == id) {
            if (curr == ls->head) {
                ls->head = curr->next;
                if (ls->head == nullptr) ls->tail = nullptr;
            } else if (curr == ls->tail) {
                ls->tail = prev;
                prev->next = nullptr;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            ls->n--;
            std::cout << "Student record deleted successfully.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    std::cout << "Student record ID not found.\n";
}

inline void displayStudents(StudentList* ls) {
    if (ls->n == 0) {
        std::cout << "No student entries recorded.\n";
        return;
    }
    StudentElement* curr = ls->head;
    while (curr != nullptr) {
        std::cout << "[ID: " << curr->data.studentID 
                  << "] Name: " << curr->data.name 
                  << " | GPA: " << curr->data.gpa << "\n";
        curr = curr->next;
    }
}

#endif