<<<<<<< HEAD
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

// Course Entity
struct Course {
    std::string courseID;
    std::string courseName;
    int credits;
    std::string department;
    int maxCapacity;
    int currentEnrollment;
    std::string instructor;
};

// Student Entity
struct Student {
    std::string studentID;
    std::string name;
    std::string major;
    int year;
    double gpa;
    std::vector<std::string> enrolledCourses;
};

inline std::string joinCourseCodes(const std::vector<std::string>& codes) {
    std::string result;
    for (size_t i = 0; i < codes.size(); ++i) {
        result += codes[i];
        if (i + 1 < codes.size()) result += ";";
    }
    return result;
}

inline std::vector<std::string> splitCourseCodes(const std::string& line) {
    std::vector<std::string> output;
    std::string token;
    for (char c : line) {
        if (c == ';') {
            if (!token.empty()) {
                output.push_back(token);
                token.clear();
            }
        } else {
            token.push_back(c);
        }
    }
    if (!token.empty()) output.push_back(token);
    return output;
}

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

=======
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

// Course Entity
struct Course {
    std::string courseID;
    std::string courseName;
    int credits;
    std::string department;
    int maxCapacity;
    int currentEnrollment;
    std::string instructor;
};

// Student Entity
struct Student {
    std::string studentID;
    std::string name;
    std::string major;
    int year;
    double gpa;
    std::vector<std::string> enrolledCourses;
};

inline std::string joinCourseCodes(const std::vector<std::string>& codes) {
    std::string result;
    for (size_t i = 0; i < codes.size(); ++i) {
        result += codes[i];
        if (i + 1 < codes.size()) result += ";";
    }
    return result;
}

inline std::vector<std::string> splitCourseCodes(const std::string& line) {
    std::vector<std::string> output;
    std::string token;
    for (char c : line) {
        if (c == ';') {
            if (!token.empty()) {
                output.push_back(token);
                token.clear();
            }
        } else {
            token.push_back(c);
        }
    }
    if (!token.empty()) output.push_back(token);
    return output;
}

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

>>>>>>> 73a84c83f1336b09682f5c7eb3f11f8df0857738
#endif