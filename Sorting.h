<<<<<<< HEAD
#ifndef SORTING_H
#define SORTING_H

#include "Structures.h"

// =========================================================
// STUDENT SORTING ALGORITHMS (Data Swapping Style)
// =========================================================

// 1. Bubble Sort: Sorts Students by Name alphabetically
inline void bubbleSortStudentsByName(StudentList* ls) {
    if (ls->n < 2) return;
    
    bool swapped;
    StudentElement* ptr1;
    StudentElement* lptr = nullptr;
    
    do {
        swapped = false;
        ptr1 = ls->head;
        
        while (ptr1->next != lptr) {
            if (ptr1->data.name > ptr1->next->data.name) {
                Student temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// 2. Selection Sort: Sorts Students by GPA descending (Highest to Lowest)
inline void selectionSortStudentsByGPADescending(StudentList* ls) {
    if (ls->n < 2) return;
    
    StudentElement* i = ls->head;
    while (i != nullptr) {
        StudentElement* maxNode = i;
        StudentElement* j = i->next;
        
        while (j != nullptr) {
            if (j->data.gpa > maxNode->data.gpa) {
                maxNode = j;
            }
            j = j->next;
        }
        
        if (maxNode != i) {
            Student temp = i->data;
            i->data = maxNode->data;
            maxNode->data = temp;
        }
        i = i->next;
    }
}

// Helper for Quick Sort: Finds the tail node of a segment
inline StudentElement* getTail(StudentElement* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

// Helper partition function for Quick Sort (Sorting by Student ID alphabetically)
inline StudentElement* partitionByID(StudentElement* head, StudentElement* end, StudentElement** newHead, StudentElement** newEnd) {
    StudentElement* pivot = end;
    StudentElement* prev = nullptr;
    StudentElement* cur = head;
    StudentElement* tail = pivot;

    while (cur != pivot) {
        if (cur->data.studentID < pivot->data.studentID) {
            if ((*newHead) == nullptr) (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            StudentElement* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == nullptr) (*newHead) = pivot;
    (*newEnd) = tail;

    return pivot;
}

// Recursive Quick Sort helper
inline StudentElement* quickSortRecur(StudentElement* head, StudentElement* end) {
    if (!head || head == end) return head;

    StudentElement *newHead = nullptr, *newEnd = nullptr;
    StudentElement* pivot = partitionByID(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        StudentElement* tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

// 3. Quick Sort: Sorts Students by ID alphabetically
inline void quickSortStudentsByID(StudentList* ls) {
    if (ls->n < 2) return;
    ls->head = quickSortRecur(ls->head, getTail(ls->head));
    ls->tail = getTail(ls->head);
}

=======
#ifndef SORTING_H
#define SORTING_H

#include "Structures.h"

// =========================================================
// STUDENT SORTING ALGORITHMS (Data Swapping Style)
// =========================================================

// 1. Bubble Sort: Sorts Students by Name alphabetically
inline void bubbleSortStudentsByName(StudentList* ls) {
    if (ls->n < 2) return;
    
    bool swapped;
    StudentElement* ptr1;
    StudentElement* lptr = nullptr;
    
    do {
        swapped = false;
        ptr1 = ls->head;
        
        while (ptr1->next != lptr) {
            if (ptr1->data.name > ptr1->next->data.name) {
                Student temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// 2. Selection Sort: Sorts Students by GPA descending (Highest to Lowest)
inline void selectionSortStudentsByGPADescending(StudentList* ls) {
    if (ls->n < 2) return;
    
    StudentElement* i = ls->head;
    while (i != nullptr) {
        StudentElement* maxNode = i;
        StudentElement* j = i->next;
        
        while (j != nullptr) {
            if (j->data.gpa > maxNode->data.gpa) {
                maxNode = j;
            }
            j = j->next;
        }
        
        if (maxNode != i) {
            Student temp = i->data;
            i->data = maxNode->data;
            maxNode->data = temp;
        }
        i = i->next;
    }
}

// Helper for Quick Sort: Finds the tail node of a segment
inline StudentElement* getTail(StudentElement* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

// Helper partition function for Quick Sort (Sorting by Student ID alphabetically)
inline StudentElement* partitionByID(StudentElement* head, StudentElement* end, StudentElement** newHead, StudentElement** newEnd) {
    StudentElement* pivot = end;
    StudentElement* prev = nullptr;
    StudentElement* cur = head;
    StudentElement* tail = pivot;

    while (cur != pivot) {
        if (cur->data.studentID < pivot->data.studentID) {
            if ((*newHead) == nullptr) (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            StudentElement* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == nullptr) (*newHead) = pivot;
    (*newEnd) = tail;

    return pivot;
}

// Recursive Quick Sort helper
inline StudentElement* quickSortRecur(StudentElement* head, StudentElement* end) {
    if (!head || head == end) return head;

    StudentElement *newHead = nullptr, *newEnd = nullptr;
    StudentElement* pivot = partitionByID(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        StudentElement* tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

// 3. Quick Sort: Sorts Students by ID alphabetically
inline void quickSortStudentsByID(StudentList* ls) {
    if (ls->n < 2) return;
    ls->head = quickSortRecur(ls->head, getTail(ls->head));
    ls->tail = getTail(ls->head);
}

>>>>>>> 73a84c83f1336b09682f5c7eb3f11f8df0857738
#endif