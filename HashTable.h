#ifndef HASHTABLEH_H
#define HASHTABLE_H

#include <iostream>
#include <string>

const int HASH_TABLE_SIZE = 31;

namespace OpenHash {

struct CourseEntry {
    std::string courseID;
    std::string courseName;
    int credits;
    std::string department;
    int maxCapacity;
    int currentEnrollment;
    std::string instructor;
    CourseEntry* next;
};

struct CourseList {
    int n;
    CourseEntry* head;
    CourseEntry* tail;
};

struct CourseHashTable {
    CourseList* ht[HASH_TABLE_SIZE];
};

inline CourseList* createEmptyCourseList() {
    CourseList* ls = new CourseList();
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

inline void createAllEmptyLists(CourseHashTable* table) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        table->ht[i] = createEmptyCourseList();
    }
}

inline CourseEntry* createCourseEntry(
    const std::string& courseID,
    const std::string& courseName,
    int credits,
    const std::string& department,
    int maxCapacity,
    int currentEnrollment,
    const std::string& instructor) {
    CourseEntry* e = new CourseEntry();
    e->courseID = courseID;
    e->courseName = courseName;
    e->credits = credits;
    e->department = department;
    e->maxCapacity = maxCapacity;
    e->currentEnrollment = currentEnrollment;
    e->instructor = instructor;
    e->next = nullptr;
    return e;
}

inline void addEnd(CourseList* ls, CourseEntry* e) {
    e->next = nullptr;
    if (ls->n == 0) {
        ls->head = e;
        ls->tail = e;
    } else {
        ls->tail->next = e;
        ls->tail = e;
    }
    ls->n++;
}

inline size_t hashCourseID(const std::string& key) {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<unsigned long>(c);
    }
    return hash % HASH_TABLE_SIZE;
}

inline CourseHashTable* createCourseHashTable() {
    CourseHashTable* ht = new CourseHashTable();
    createAllEmptyLists(ht);
    return ht;
}

inline void insertCourseHash(CourseHashTable* ht,
                             const std::string& courseID,
                             const std::string& courseName,
                             int credits,
                             const std::string& department,
                             int maxCapacity,
                             int currentEnrollment,
                             const std::string& instructor) {
    int index = static_cast<int>(hashCourseID(courseID));
    CourseList* list = ht->ht[index];

    CourseEntry* e = list->head;
    while (e != nullptr) {
        if (e->courseID == courseID) {
            e->courseName = courseName;
            e->credits = credits;
            e->department = department;
            e->maxCapacity = maxCapacity;
            e->currentEnrollment = currentEnrollment;
            e->instructor = instructor;
            return;
        }
        e = e->next;
    }

    addEnd(list, createCourseEntry(courseID, courseName, credits, department, maxCapacity, currentEnrollment, instructor));
}

inline CourseEntry* searchCourseHash(CourseHashTable* ht, const std::string& courseID) {
    int index = static_cast<int>(hashCourseID(courseID));
    CourseList* list = ht->ht[index];

    if (list->n == 0) {
        return nullptr;
    }

    CourseEntry* e = list->head;
    while (e != nullptr) {
        if (e->courseID == courseID) {
            return e;
        }
        e = e->next;
    }
    return nullptr;
}

inline bool removeCourseHash(CourseHashTable* ht, const std::string& courseID) {
    int index = static_cast<int>(hashCourseID(courseID));
    CourseList* list = ht->ht[index];

    if (list->n == 0) {
        return false;
    }

    CourseEntry* e = list->head;
    CourseEntry* prev = nullptr;

    while (e != nullptr) {
        if (e->courseID == courseID) {
            if (prev == nullptr) {
                list->head = e->next;
                if (list->head == nullptr) {
                    list->tail = nullptr;
                }
            } else {
                prev->next = e->next;
                if (prev->next == nullptr) {
                    list->tail = prev;
                }
            }
            delete e;
            list->n--;
            return true;
        }
        prev = e;
        e = e->next;
    }
    return false;
}

inline void displayCourseHashTable(CourseHashTable* ht) {
    std::cout << "Course hash table contents:\n";
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        CourseList* list = ht->ht[i];
        std::cout << i << "\t-->";
        if (list->n != 0) {
            CourseEntry* e = list->head;
            while (e != nullptr) {
                std::cout << " " << e->courseID;
                e = e->next;
                if (e != nullptr) {
                    std::cout << " ->";
                }
            }
        } else {
            std::cout << "NULL";
        }
        std::cout << std::endl;
    }
}

inline void clearCourseHashTable(CourseHashTable* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        CourseEntry* e = ht->ht[i]->head;
        while (e != nullptr) {
            CourseEntry* next = e->next;
            delete e;
            e = next;
        }
        ht->ht[i]->head = nullptr;
        ht->ht[i]->tail = nullptr;
        ht->ht[i]->n = 0;
    }
}

} // namespace OpenHash

using OpenHash::CourseEntry;
using OpenHash::CourseHashTable;
using OpenHash::createCourseHashTable;
using OpenHash::insertCourseHash;
using OpenHash::searchCourseHash;
using OpenHash::removeCourseHash;
using OpenHash::displayCourseHashTable;
using OpenHash::clearCourseHashTable;

#endif
