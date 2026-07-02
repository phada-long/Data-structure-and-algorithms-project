#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

const int HASH_TABLE_SIZE = 31;

struct CourseEntry {
    std::string courseID;
    std::string courseName;
    int credits;
    std::string department;
    int maxCapacity;
    int currentEnrollment;
    std::string instructor;
};

struct CourseHashTable {
    CourseEntry ht[HASH_TABLE_SIZE];
};

inline void initializeCourseHashTable(CourseHashTable& table) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        table.ht[i] = CourseEntry{};
    }
}

inline CourseHashTable createCourseHashTable() {
    CourseHashTable table;
    initializeCourseHashTable(table);
    return table;
}

inline size_t hashCourseID(const std::string& courseID) {
    size_t key = 0;
    for (char c : courseID) {
        key += static_cast<unsigned char>(c);
    }
    return key % HASH_TABLE_SIZE;
}

inline void insertCourseHash(CourseHashTable& table,
    const std::string& courseID,
    const std::string& courseName,
    int credits,
    const std::string& department,
    int maxCapacity,
    int currentEnrollment,
    const std::string& instructor) {
    int index = static_cast<int>(hashCourseID(courseID));
    table.ht[index].courseID = courseID;
    table.ht[index].courseName = courseName;
    table.ht[index].credits = credits;
    table.ht[index].department = department;
    table.ht[index].maxCapacity = maxCapacity;
    table.ht[index].currentEnrollment = currentEnrollment;
    table.ht[index].instructor = instructor;
}

inline CourseEntry* searchCourseHash(CourseHashTable& table, const std::string& courseID) {
    int index = static_cast<int>(hashCourseID(courseID));
    if (table.ht[index].courseID == courseID) {
        return &table.ht[index];
    }
    return nullptr;
}

inline bool removeCourseHash(CourseHashTable& table, const std::string& courseID) {
    int index = static_cast<int>(hashCourseID(courseID));
    if (table.ht[index].courseID != courseID) {
        return false;
    }

    table.ht[index] = CourseEntry{};
    return true;
}

inline void displayCourseHashTable(const CourseHashTable& table) {
    std::cout << "Course hash table contents:\n";
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        std::cout << i << "\t-->";
        const CourseEntry& entry = table.ht[i];
        if (entry.courseID.empty()) {
            std::cout << "NULL";
        } else {
            std::cout << " " << entry.courseID
                      << " | " << entry.courseName
                      << " | Credits: " << entry.credits
                      << " | Dept: " << entry.department;
        }
        std::cout << std::endl;
    }
}

inline void clearCourseHashTable(CourseHashTable& table) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        table.ht[i] = CourseEntry{};
    }
}

#endif
