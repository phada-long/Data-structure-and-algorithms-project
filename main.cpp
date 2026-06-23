#include <iostream>
#include <limits>
#include <string>
#include "LinkedList.h"
#include "Sorting.h"
#include "FileIO.h"
#include "Queue.h"
#include "HashTable.h"
#include <filesystem>

// Force all File I/O to use the workspace project folder
std::filesystem::path g_project_root = std::filesystem::path(__FILE__).parent_path();

void displayMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "   UNIVERSITY COURSE REGISTRATION SYSTEM   \n";
    std::cout << "=========================================\n";
    std::cout << "1. Add a Student\n";
    std::cout << "2. Display All Students\n";
    std::cout << "3. Update Student GPA\n";
    std::cout << "4. Delete Student by ID\n";
    std::cout << "5. Add a Course\n";
    std::cout << "6. Display All Courses\n";
    std::cout << "7. Sort Students by Name (Bubble Sort)\n";
    std::cout << "8. Sort Students by GPA (Selection Sort Descending)\n";
    std::cout << "9. Sort Students by ID (Quick Sort)\n";
    std::cout << "10. Search Course by Code (HashTable)\n";
    std::cout << "11. Display Course (HashTable)\n";
    std::cout << "12. Enqueue Waitlist Request (Queue)\n";
    std::cout << "13. Dequeue Waitlist Request (Queue)\n";
    std::cout << "14. Display Waiting Queue (Queue)\n";
    std::cout << "15. Save Database to CSV\n";
    std::cout << "16. Exit System\n";
    std::cout << "Select an option (1-16): ";
}

int main() {
    StudentList* studentList = createStudentList();
    CourseList* courseList = createCourseList();
    CourseHashTable* courseTable = createCourseHashTable();
    WaitQueue* waitQueue = createWaitQueue();
    int choice;

    // Automatically load data at startup so nothing gets lost
    loadStudentsFromCSV(studentList, "students.csv");
    loadCoursesFromCSV(courseList, "courses.csv");

    // Populate hash table from loaded course list
    CourseElement* currCourse = courseList->head;
    while (currCourse != nullptr) {
        insertCourseHash(courseTable,
                         currCourse->data.courseID,
                         currCourse->data.courseName,
                         currCourse->data.credits,
                         currCourse->data.department,
                         currCourse->data.maxCapacity,
                         currCourse->data.currentEnrollment,
                         currCourse->data.instructor);
        currCourse = currCourse->next;
    }

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch(choice) {
            case 1: {
                Student s;
                std::cout << "Enter Student ID: "; std::getline(std::cin, s.studentID);
                std::cout << "Enter Full Name: "; std::getline(std::cin, s.name);
                std::cout << "Enter Major: "; std::getline(std::cin, s.major);
                std::cout << "Enter Year: "; std::cin >> s.year;
                std::cout << "Enter GPA: "; std::cin >> s.gpa;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter enrolled course IDs separated by semicolons (optional): ";
                std::string enrolledLine;
                std::getline(std::cin, enrolledLine);
                s.enrolledCourses = splitCourseCodes(enrolledLine);
                insertStudentEnd(studentList, s);
                std::cout << "Student added successfully!\n";
                break;
            }
            case 2:
                std::cout << "\n--- Student Records ---\n";
                displayStudents(studentList);
                break;
            case 3: {
                std::string id; double newGpa;
                std::cout << "Enter Student ID to update: "; std::getline(std::cin, id);
                std::cout << "Enter New GPA: "; std::cin >> newGpa;
                if (updateStudentGPA(studentList, id, newGpa)) {
                    std::cout << "GPA updated successfully!\n";
                } else {
                    std::cout << "Student ID target not found.\n";
                }
                break;
            }
            case 4: {
                std::string id;
                std::cout << "Enter Student ID to delete: "; std::getline(std::cin, id);
                deleteStudentByID(studentList, id);
                break;
            }
            case 5: {
                Course c;
                std::cout << "Enter Course ID: "; std::getline(std::cin, c.courseID);
                std::cout << "Enter Course Name: "; std::getline(std::cin, c.courseName);
                std::cout << "Enter Credits: "; std::cin >> c.credits;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Department: "; std::getline(std::cin, c.department);
                std::cout << "Enter Max Capacity: "; std::cin >> c.maxCapacity;
                std::cout << "Enter Current Enrollment: "; std::cin >> c.currentEnrollment;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Instructor: "; std::getline(std::cin, c.instructor);
                insertCourseEnd(courseList, c);
                insertCourseHash(courseTable,
                                 c.courseID,
                                 c.courseName,
                                 c.credits,
                                 c.department,
                                 c.maxCapacity,
                                 c.currentEnrollment,
                                 c.instructor);
                std::cout << "Course added successfully!\n";
                break;
            }
            case 6:
                std::cout << "\n--- Registered Courses ---\n";
                displayCourses(courseList);
                break;
            case 7:
                bubbleSortStudentsByName(studentList);
                std::cout << "Students sorted by name successfully!\n";
                break;
            case 8:
                selectionSortStudentsByGPADescending(studentList);
                std::cout << "Students sorted by GPA (Descending) successfully!\n";
                break;
            case 9:
                quickSortStudentsByID(studentList);
                std::cout << "Students sorted by ID via Quick Sort successfully!\n";
                break;
            case 10: {
                std::string courseID;
                std::cout << "Enter Course ID to search (HashTable): ";
                std::getline(std::cin, courseID);
                CourseEntry* result = searchCourseHash(courseTable, courseID);
                if (result != nullptr) {
                    std::cout << "Course found: " << result->courseID
                              << " | " << result->courseName
                              << " | Credits: " << result->credits
                              << " | Dept: " << result->department
                              << " | Enrollment: " << result->currentEnrollment << "/" << result->maxCapacity
                              << " | Instructor: " << result->instructor << "\n";
                } else {
                    std::cout << "Course not found in hash table.\n";
                }
                break;
            }
            case 11:
                displayCourseHashTable(courseTable);
                break;
            case 12: {
                std::string studentID, courseID;
                std::cout << "Enter Student ID for waitlist : "; std::getline(std::cin, studentID);
                std::cout << "Enter Course ID for waitlist : "; std::getline(std::cin, courseID);
                enqueueRequest(waitQueue, studentID, courseID);
                std::cout << "Enrollment request added to waiting queue.\n";
                break;
            }
            case 13: {
                EnrollmentRequest request;
                if (dequeueRequest(waitQueue, request)) {
                    std::cout << "Dequeued waiting student: " << request.studentID
                              << " for course " << request.courseID << "\n";
                } else {
                    std::cout << "Waiting queue is empty.\n";
                }
                break;
            }
            case 14:
                displayWaitQueue(waitQueue);
                break;
            case 15:
                saveStudentsToCSV(studentList, "students.csv");
                saveCoursesToCSV(courseList, "courses.csv");
                break;
            case 16:
                // Auto-save on exit to protect project data
                saveStudentsToCSV(studentList, "students.csv");
                saveCoursesToCSV(courseList, "courses.csv");
                std::cout << "Exiting System... Data saved. Goodbye.\n";
                break;
            default:
                std::cout << "Invalid selection. Please input numbers 1 to 16.\n";
        }
    } while (choice != 16);

    return 0;
}