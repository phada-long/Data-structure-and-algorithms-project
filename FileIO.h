#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include <filesystem>

// Global project root (defined in main.cpp)
extern std::filesystem::path g_project_root;

// Utility: trim whitespace from both ends
inline std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Save Student List to CSV
inline void saveStudentsToCSV(StudentList* ls, std::string filename) {
    std::filesystem::path filePath = g_project_root / filename;
    std::ofstream file(filePath.string());
    if (!file.is_open()) {
        std::cout << "Error opening file for saving!\n";
        return;
    }
    int written = 0;
    StudentElement* curr = ls->head;
    while (curr != nullptr) {
        file << curr->data.studentID << ","
             << curr->data.name << ","
             << curr->data.gpa << "\n";
        curr = curr->next;
        written++;
    }
    file.close();
    std::cout << "Student records successfully saved (" << written << ") to " << filePath.string() << "\n";
}

// Load Student List from CSV
inline void loadStudentsFromCSV(StudentList* ls, std::string filename) {
    std::filesystem::path filePath = g_project_root / filename;
    std::ifstream file(filePath.string());
    if (!file.is_open()) {
        std::cout << "No existing student database found at " << filePath.string() << ". Starting fresh.\n";
        return;
    }

    std::string line;
    int loaded = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Student s;
        std::string gpaStr;

        std::getline(ss, s.studentID, ',');
        std::getline(ss, s.name, ',');
        // read remainder of line for GPA (handles missing trailing comma)
        std::getline(ss, gpaStr);

        s.studentID = trim(s.studentID);
        s.name = trim(s.name);
        gpaStr = trim(gpaStr);

        if(!s.studentID.empty() && !s.name.empty() && !gpaStr.empty()) {
            try {
                s.gpa = std::stod(gpaStr);
                insertStudentEnd(ls, s);
                loaded++;
            } catch(...) {
                // skip malformed GPA field
                continue;
            }
        }
    }
    file.close();
    std::cout << "Student records loaded: " << loaded << " from " << filePath.string() << "\n";
}

// Save Course List to CSV
inline void saveCoursesToCSV(CourseList* ls, std::string filename) {
    std::filesystem::path filePath = g_project_root / filename;
    std::ofstream file(filePath.string());
    if (!file.is_open()) {
        std::cout << "Error opening file for saving!\n";
        return;
    }

    int written = 0;
    CourseElement* curr = ls->head;
    while (curr != nullptr) {
        file << curr->data.courseID << ","
             << curr->data.courseName << ","
             << curr->data.credits << "\n";
        curr = curr->next;
        written++;
    }
    file.close();
    std::cout << "Course records successfully saved (" << written << ") to " << filePath.string() << "\n";
}

// Load Course List from CSV
inline void loadCoursesFromCSV(CourseList* ls, std::string filename) {
    std::filesystem::path filePath = g_project_root / filename;
    std::ifstream file(filePath.string());
    if (!file.is_open()) {
        std::cout << "No existing course database found at " << filePath.string() << ". Starting fresh.\n";
        return;
    }

    std::string line;
    int loadedC = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Course c;
        std::string creditsStr;

        std::getline(ss, c.courseID, ',');
        std::getline(ss, c.courseName, ',');
        // read remainder of line for credits
        std::getline(ss, creditsStr);

        c.courseID = trim(c.courseID);
        c.courseName = trim(c.courseName);
        creditsStr = trim(creditsStr);

        if(!c.courseID.empty() && !c.courseName.empty() && !creditsStr.empty()) {
            try {
                c.credits = std::stoi(creditsStr);
                insertCourseEnd(ls, c);
                loadedC++;
            } catch(...) {
                continue;
            }
        }
    }
    file.close();
    std::cout << "Course records loaded: " << loadedC << " from " << filePath.string() << "\n";
}

#endif