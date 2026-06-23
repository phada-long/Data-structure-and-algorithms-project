#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Sorting.h"
#include "FileIO.h"

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
    std::cout << "10. Save Database to CSV\n";
    std::cout << "11. Exit System\n";
    std::cout << "Select an option (1-11): ";
}

int main() {
    StudentList* studentList = createStudentList();
    CourseList* courseList = createCourseList();
    int choice;

    // Automatically load data at startup so nothing gets lost
    loadStudentsFromCSV(studentList, "students.csv");
    loadCoursesFromCSV(courseList, "courses.csv");

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch(choice) {
            case 1: {
                Student s;
                std::cout << "Enter Student ID: "; std::getline(std::cin, s.studentID);
                std::cout << "Enter Name: "; std::getline(std::cin, s.name);
                std::cout << "Enter GPA: "; std::cin >> s.gpa;
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
                insertCourseEnd(courseList, c);
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
            case 10:
                saveStudentsToCSV(studentList, "students.csv");
                saveCoursesToCSV(courseList, "courses.csv");
                break;
            case 11:
                // Auto-save on exit to protect project data
                saveStudentsToCSV(studentList, "students.csv");
                saveCoursesToCSV(courseList, "courses.csv");
                std::cout << "Exiting System... Data saved. Goodbye.\n";
                break;
            default:
                std::cout << "Invalid selection. Please input numbers 1 to 11.\n";
        }
    } while (choice != 11);

    return 0;
}