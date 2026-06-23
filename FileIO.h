#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <sstream>
#include "LinkedList.h"

// Save Student List to CSV
inline void saveStudentsToCSV(StudentList* ls, std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for saving!\n";
        return;
    }
    
    StudentElement* curr = ls->head;
    while (curr != nullptr) {
        file << curr->data.studentID << ","
             << curr->data.name << ","
             << curr->data.gpa << "\n";
        curr = curr->next;
    }
    file.close();
    std::cout << "Student records successfully saved to " << filename << "\n";
}

// Load Student List from CSV
inline void loadStudentsFromCSV(StudentList* ls, std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No existing student database found. Starting fresh.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Student s;
        std::string gpaStr;

        std::getline(ss, s.studentID, ',');
        std::getline(ss, s.name, ',');
        std::getline(ss, gpaStr, ',');
        
        if(!s.studentID.empty() && !s.name.empty()) {
            s.gpa = std::stod(gpaStr);
            insertStudentEnd(ls, s);
        }
    }
    file.close();
    std::cout << "Student records successfully loaded from " << filename << "\n";
}

// Save Course List to CSV
inline void saveCoursesToCSV(CourseList* ls, std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for saving!\n";
        return;
    }
    
    CourseElement* curr = ls->head;
    while (curr != nullptr) {
        file << curr->data.courseID << ","
             << curr->data.courseName << ","
             << curr->data.credits << "\n";
        curr = curr->next;
    }
    file.close();
    std::cout << "Course records successfully saved to " << filename << "\n";
}

// Load Course List from CSV
inline void loadCoursesFromCSV(CourseList* ls, std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No existing course database found. Starting fresh.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Course c;
        std::string creditsStr;

        std::getline(ss, c.courseID, ',');
        std::getline(ss, c.courseName, ',');
        std::getline(ss, creditsStr, ',');
        
        if(!c.courseID.empty() && !c.courseName.empty()) {
            c.credits = std::stoi(creditsStr);
            insertCourseEnd(ls, c);
        }
    }
    file.close();
    std::cout << "Course records successfully loaded from " << filename << "\n";
}

#endif