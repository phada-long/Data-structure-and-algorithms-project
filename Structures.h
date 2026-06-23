#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

// Course Entity
struct Course {
    std::string courseID;
    std::string courseName;
    int credits;
};

// Student Entity
struct Student {
    std::string studentID;
    std::string name;
    double gpa;
};

// =========================================================
// COURSE LINKED LIST WRAPPERS (Teacher Seak Leng Style)
// =========================================================
struct CourseElement {
    Course data;
    CourseElement* next;
};

struct CourseList {
    int n;
    CourseElement* head;
    CourseElement* tail;
};

// =========================================================
// STUDENT LINKED LIST WRAPPERS (Teacher Seak Leng Style)
// =========================================================
struct StudentElement {
    Student data;
    StudentElement* next;
};

struct StudentList {
    int n;
    StudentElement* head;
    StudentElement* tail;
};

#endif