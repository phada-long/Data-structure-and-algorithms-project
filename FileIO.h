#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "Queue.h"
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
             << curr->data.major << ","
             << curr->data.year << ","
             << curr->data.gpa << ","
             << joinCourseCodes(curr->data.enrolledCourses) << "\n";
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
        std::string yearStr, gpaStr, enrolledStr;

        std::getline(ss, s.studentID, ',');
        std::getline(ss, s.name, ',');
        std::getline(ss, s.major, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, gpaStr, ',');
        std::getline(ss, enrolledStr);

        s.studentID = trim(s.studentID);
        s.name = trim(s.name);
        s.major = trim(s.major);
        yearStr = trim(yearStr);
        gpaStr = trim(gpaStr);
        enrolledStr = trim(enrolledStr);

        if(!s.studentID.empty() && !s.name.empty() && !yearStr.empty() && !gpaStr.empty()) {
            try {
                s.year = std::stoi(yearStr);
                s.gpa = std::stod(gpaStr);
                s.enrolledCourses = splitCourseCodes(enrolledStr);
                insertStudentEnd(ls, s);
                loaded++;
            } catch(...) {
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
             << curr->data.credits << ","
             << curr->data.department << ","
             << curr->data.maxCapacity << ","
             << curr->data.currentEnrollment << ","
             << curr->data.instructor << "\n";
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
        std::string creditsStr, maxCapacityStr, currentEnrollmentStr;

        std::getline(ss, c.courseID, ',');
        std::getline(ss, c.courseName, ',');
        std::getline(ss, creditsStr, ',');
        std::getline(ss, c.department, ',');
        std::getline(ss, maxCapacityStr, ',');
        std::getline(ss, currentEnrollmentStr, ',');
        std::getline(ss, c.instructor);

        c.courseID = trim(c.courseID);
        c.courseName = trim(c.courseName);
        creditsStr = trim(creditsStr);
        c.department = trim(c.department);
        maxCapacityStr = trim(maxCapacityStr);
        currentEnrollmentStr = trim(currentEnrollmentStr);
        c.instructor = trim(c.instructor);

        if(!c.courseID.empty() && !c.courseName.empty() && !creditsStr.empty() && !maxCapacityStr.empty() && !currentEnrollmentStr.empty()) {
            try {
                c.credits = std::stoi(creditsStr);
                c.maxCapacity = std::stoi(maxCapacityStr);
                c.currentEnrollment = std::stoi(currentEnrollmentStr);
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

// Load Queue from CSV
inline void loadQueueFromCSV(WaitQueue& q, std::string filename) {
    std::filesystem::path filePath = g_project_root / filename;
    std::ifstream file(filePath.string());
    if (!file.is_open()) {
        std::cout << "No existing queue database found at " << filePath.string() << ". Starting fresh.\n";
        return;
    }

    std::string line;
    int loaded = 0;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string studentID, courseID;

        std::getline(ss, studentID, ',');
        std::getline(ss, courseID);

        studentID = trim(studentID);
        courseID = trim(courseID);

        if(!studentID.empty() && !courseID.empty()) {
            enqueueRequest(q, studentID, courseID);
            loaded++;
        }
    }
    file.close();
    std::cout << "Queue records loaded: " << loaded << " from " << filePath.string() << "\n";
}

// Save Queue to CSV
inline void saveQueueToCSV(const WaitQueue& q, std::string filename) {
    std::filesystem::path filePath = g_project_root / filename;
    std::ofstream file(filePath.string());
    if (!file.is_open()) {
        std::cout << "Error opening file for saving!\n";
        return;
    }

    // Write header
    file << "studentID,courseID\n";

    int written = 0;
    if (!isWaitQueueEmpty(q)) {
        for (int i = q.front; i <= q.rear; i++) {
            file << q.Q[i].studentID << ","
                 << q.Q[i].courseID << "\n";
            written++;
        }
    }
    file.close();
    std::cout << "Queue records successfully saved (" << written << ") to " << filePath.string() << "\n";
}

#endif