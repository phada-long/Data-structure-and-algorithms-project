#include <iostream>
#include <limits>
#include <string>
#include <filesystem>

#include "LinkedList.h"
#include "Sorting.h"
#include "FileIO.h"
#include "Queue.h"
#include "HashTable.h"
#include "UndoStack.h"
#include "Tree.h"

using namespace std;

// Global project path
std::filesystem::path g_project_root = std::filesystem::path(__FILE__).parent_path();

// ================= UNDO SYSTEM OBJECT =================
UndoStack undoStack;

// ================= MENU =================
void displayMenu() {
    cout << "\n=========================================\n";
    cout << "   UNIVERSITY COURSE REGISTRATION SYSTEM   \n";
    cout << "=========================================\n";
    cout << "1. Add a Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Update Student GPA\n";
    cout << "4. Delete Student by ID\n";
    cout << "5. Add a Course\n";
    cout << "6. Display All Courses\n";
    cout << "7. Sort Students by Name\n";
    cout << "8. Sort Students by GPA\n";
    cout << "9. Sort Students by ID\n";
    cout << "10. Search Course (HashTable)\n";
    cout << "11. Display Course (HashTable)\n";
    cout << "12. Enqueue Waitlist\n";
    cout << "13. Dequeue Waitlist\n";
    cout << "14. Display Queue\n";
    cout << "15. Save CSV\n";
    cout << "16. Exit\n";
    cout << "17. Undo Last Action\n";
    cout << "18. Show Action History\n";
    cout << "19. Display Department Tree\n";
    cout << "20. Search Department\n";
    cout << "Select option: ";
}

// ================= MAIN =================
int main() {

    StudentList* studentList = createStudentList();
    CourseList* courseList = createCourseList();
    CourseHashTable* courseTable = createCourseHashTable();
    WaitQueue* waitQueue = createWaitQueue();
    DepartmentNode *departmentTree = nullptr;

    int choice;

    // Load data
    loadStudentsFromCSV(studentList, "students.csv");
    loadCoursesFromCSV(courseList, "courses.csv");
    loadQueueFromCSV(waitQueue, "queue.csv");

    // Build department tree
    buildDepartmentTree(departmentTree, courseList);

    // Build hash table
    CourseElement* curr = courseList->head;
    while (curr != nullptr) {
        insertCourseHash(courseTable,
            curr->data.courseID,
            curr->data.courseName,
            curr->data.credits,
            curr->data.department,
            curr->data.maxCapacity,
            curr->data.currentEnrollment,
            curr->data.instructor);

        curr = curr->next;
    }

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            Student s;
            cout << "Enter Student ID: ";
            getline(cin, s.studentID);
            cout << "Enter Full Name: ";
            getline(cin, s.name);
            cout << "Enter Major: ";
            getline(cin, s.major);
            cout << "Enter Year: ";
            cin >> s.year;
            cout << "Enter GPA: ";
            cin >> s.gpa;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter enrolled courses: ";
            string line;
            getline(cin, line);
            s.enrolledCourses = splitCourseCodes(line);
            insertStudentEnd(studentList, s);
            // ⭐ UNDO TRACKING
            undoStack.pushAction(ADD_STUDENT,
                                 "ID:" + s.studentID + " Name:" + s.name);
            cout << "Student added successfully!\n";
            break;
        }
        case 2:
            displayStudents(studentList);
            break;

        case 3:
        {
            string id;
            double gpa;
            cout << "Enter ID: ";
            getline(cin, id);
            cout << "Enter new GPA: ";
            cin >> gpa;
            cin.ignore();
            if (updateStudentGPA(studentList, id, gpa))
            {
                undoStack.pushAction(UPDATE_GPA,
                                     "ID:" + id + " GPA updated");
                cout << "Updated successfully!\n";
            }
            else
            {
                cout << "Student not found!\n";
            }
            break;
        }

        case 4:
        {
            string id;

            cout << "Enter ID to delete: ";
            getline(cin, id);

            deleteStudentByID(studentList, id);

            undoStack.pushAction(DELETE_STUDENT,
                                 "Deleted ID:" + id);

            cout << "Deleted successfully!\n";
            break;
        }

        case 5:
        {
            Course c;

            cout << "Enter Course ID: ";
            getline(cin, c.courseID);

            cout << "Enter Name: ";
            getline(cin, c.courseName);

            cout << "Enter Credits: ";
            cin >> c.credits;
            cin.ignore();

            cout << "Enter Department: ";
            getline(cin, c.department);

            cout << "Enter Max Capacity: ";
            cin >> c.maxCapacity;

            cout << "Enter Current Enrollment: ";
            cin >> c.currentEnrollment;
            cin.ignore();

            cout << "Enter Instructor: ";
            getline(cin, c.instructor);

            insertCourseEnd(courseList, c);

            // Add department into Tree
            departmentTree =
                insertDepartment(
                    departmentTree,
                    c.department);

            insertCourseHash(courseTable,
                             c.courseID,
                             c.courseName,
                             c.credits,
                             c.department,
                             c.maxCapacity,
                             c.currentEnrollment,
                             c.instructor);

            undoStack.pushAction(ADD_COURSE,
                                 "Course:" + c.courseID);

            cout << "Course added!\n";
            break;
        }

        case 6:
            displayCourses(courseList);
            break;

        case 7:
            bubbleSortStudentsByName(studentList);
            break;

        case 8:
            selectionSortStudentsByGPADescending(studentList);
            break;

        case 9:
            quickSortStudentsByID(studentList);
            break;

        case 10:
        {
            string id;
            cout << "Enter Course ID: ";
            getline(cin, id);

            CourseEntry *res = searchCourseHash(courseTable, id);

            if (res)
                cout << res->courseName << endl;
            else
                cout << "Not found\n";

            break;
        }

        case 11:
            displayCourseHashTable(courseTable);
            break;

        case 12:
        {
            string sid, cid;
            cout << "Student ID: ";
            getline(cin, sid);

            cout << "Course ID: ";
            getline(cin, cid);

            enqueueRequest(waitQueue, sid, cid);

            undoStack.pushAction(DROP_COURSE,
                                 sid + " -> " + cid);

            break;
        }

        case 13:
        {
            EnrollmentRequest r;
            dequeueRequest(waitQueue, r);
            break;
        }

        case 14:
            displayWaitQueue(waitQueue);
            break;

        case 15:
            saveStudentsToCSV(studentList, "students.csv");
            saveCoursesToCSV(courseList, "courses.csv");
            saveQueueToCSV(waitQueue, "queue.csv");
            break;

        case 17:
            undoStack.undo();
            break;

        case 18:
            undoStack.showHistory();
            break;

        case 19:
        {
            cout << "\n===== DEPARTMENT TREE =====\n";
            inorderDepartment(departmentTree);
            break;
        }

        case 20:
        {
            string dept;
            cout << "Enter Department Name: ";
            getline(cin, dept);
            DepartmentNode *result =
                searchDepartment(departmentTree, dept);
            if (result)
                cout << "Department Found: "
                     << result->department << endl;
            else
                cout << "Department Not Found\n";

            break;
        }

        default:
            cout << "Invalid option!\n";
        }

    } while (choice != 16);


    return 0;
}