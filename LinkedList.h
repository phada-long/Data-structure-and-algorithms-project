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
    
    std::cout << "=============================================================\n";
    CourseElement* curr = ls->head;
    while (curr != nullptr) {
        // Line 1: Course ID and Course Name
        std::string line1 = "   Course ID: " + curr->data.courseID;
        line1 += std::string(30 - (13 + curr->data.courseID.length()), ' ');
        line1 += "Course Name: " + curr->data.courseName;
        line1 = line1.substr(0, 57);
        line1 += std::string(57 - line1.length(), ' ');
        std::cout << "|" << line1 << "|\n";
        
        // Line 2: Credits and Department
        std::string creditsStr = std::to_string(curr->data.credits);
        std::string line2 = "   Credits: " + creditsStr;
        line2 += std::string(31 - (11 + creditsStr.length()), ' ');
        line2 += "Department: " + curr->data.department;
        line2 = line2.substr(0, 57);
        line2 += std::string(57 - line2.length(), ' ');
        std::cout << "|" << line2 << "|\n";
        
        // Line 3: Instructor
        std::string line3 = "   Instructor: " + curr->data.instructor;
        line3 = line3.substr(0, 57);
        line3 += std::string(57 - line3.length(), ' ');
        std::cout << "|" << line3 << "|\n";
        
        // Line 4: Capacity
        std::string capacityStr = std::to_string(curr->data.currentEnrollment) + "/" + std::to_string(curr->data.maxCapacity);
        std::string line4 = "   Capacity: " + capacityStr;
        line4 = line4.substr(0, 57);
        line4 += std::string(57 - line4.length(), ' ');
        std::cout << "|" << line4 << "|\n";
        
        std::cout << "=============================================================\n";
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
    
    std::cout << "=============================================================\n";
    StudentElement* curr = ls->head;
    while (curr != nullptr) {
        // Line 1: ID and Year
        std::string line1 = "   ID: " + curr->data.studentID;
        line1 += std::string(30 - (6 + curr->data.studentID.length()), ' ');
        line1 += "Year: " + std::to_string(curr->data.year);
        line1 = line1.substr(0, 57);
        line1 += std::string(57 - line1.length(), ' ');
        std::cout << "|" << line1 << "|\n";
        
        // Line 2: Name and Major
        std::string line2 = "   Name: " + curr->data.name;
        line2 += std::string(28 - (8 + curr->data.name.length()), ' ');
        line2 += "Major: " + curr->data.major;
        line2 = line2.substr(0, 57);
        line2 += std::string(57 - line2.length(), ' ');
        std::cout << "|" << line2 << "|\n";
        
        // Line 3: GPA
        std::string gpaStr = std::to_string(curr->data.gpa);
        gpaStr = gpaStr.substr(0, gpaStr.find('.') + 3);  // Limit to 2 decimal places
        std::string line3 = "   GPA: " + gpaStr;
        line3 += std::string(57 - line3.length(), ' ');
        std::cout << "|" << line3 << "|\n";
        
        // Line 4: Enrolled
        std::string enrolledStr = joinCourseCodes(curr->data.enrolledCourses);
        std::string line4 = "   Enrolled: " + enrolledStr;
        line4 = line4.substr(0, 57);
        line4 += std::string(57 - line4.length(), ' ');
        std::cout << "|" << line4 << "|\n";
        
        std::cout << "=============================================================\n";
        curr = curr->next;
    }
}

#endif