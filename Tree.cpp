#include "Tree.h"
#include <iostream>
#include <vector>

using namespace std;

struct CourseNode {
    string courseID;
    string courseName;
    int credits;

    CourseNode(string id, string name, int c) {
        courseID = id;
        courseName = name;
        credits = c;
    }
};

struct DepartmentNode {
    string deptName;
    vector<CourseNode*> courses;

    DepartmentNode(string name) {
        deptName = name;
    }
};

struct FacultyNode {
    string facultyName;
    vector<DepartmentNode*> departments;

    FacultyNode(string name) {
        facultyName = name;
    }
};

vector<FacultyNode*> faculties;

void CourseTree::addFaculty(string facultyName) {

    faculties.push_back(new FacultyNode(facultyName));

    cout << "Faculty added." << endl;
}

void CourseTree::addDepartment(string facultyName,
                               string deptName) {

    for (int i = 0; i < faculties.size(); i++) {

        if (faculties[i]->facultyName == facultyName) {

            faculties[i]->departments.push_back(
                new DepartmentNode(deptName)
            );

            cout << "Department added." << endl;
            return;
        }
    }

    cout << "Faculty not found." << endl;
}

void CourseTree::addCourse(string deptName,
                           string id,
                           string name,
                           int credits) {

    for (int i = 0; i < faculties.size(); i++) {

        for (int j = 0; j < faculties[i]->departments.size(); j++) {

            DepartmentNode* dept =
                faculties[i]->departments[j];

            if (dept->deptName == deptName) {

                dept->courses.push_back(
                    new CourseNode(id, name, credits)
                );

                cout << "Course added." << endl;
                return;
            }
        }
    }

    cout << "Department not found." << endl;
}

void CourseTree::deleteDepartment(string deptName) {

    for (int i = 0; i < faculties.size(); i++) {

        for (int j = 0; j < faculties[i]->departments.size(); j++) {

            if (faculties[i]->departments[j]->deptName
                == deptName) {

                faculties[i]->departments.erase(
                    faculties[i]->departments.begin() + j
                );

                cout << "Department deleted." << endl;
                return;
            }
        }
    }

    cout << "Department not found." << endl;
}

void CourseTree::deleteCourse(string id) {

    for (int i = 0; i < faculties.size(); i++) {

        for (int j = 0; j < faculties[i]->departments.size(); j++) {

            DepartmentNode* dept =
                faculties[i]->departments[j];

            for (int k = 0; k < dept->courses.size(); k++) {

                if (dept->courses[k]->courseID == id) {

                    dept->courses.erase(
                        dept->courses.begin() + k
                    );

                    cout << "Course deleted." << endl;
                    return;
                }
            }
        }
    }

    cout << "Course not found." << endl;
}

void CourseTree::searchCourse(string id) {

    for (int i = 0; i < faculties.size(); i++) {

        for (int j = 0; j < faculties[i]->departments.size(); j++) {

            DepartmentNode* dept =
                faculties[i]->departments[j];

            for (int k = 0; k < dept->courses.size(); k++) {

                CourseNode* course =
                    dept->courses[k];

                if (course->courseID == id) {

                    cout << "\nFound Course\n";

                    cout << "Faculty    : "
                         << faculties[i]->facultyName
                         << endl;

                    cout << "Department : "
                         << dept->deptName
                         << endl;

                    cout << "Course ID  : "
                         << course->courseID
                         << endl;

                    cout << "Course Name: "
                         << course->courseName
                         << endl;

                    cout << "Credits    : "
                         << course->credits
                         << endl;

                    return;
                }
            }
        }
    }

    cout << "Course not found." << endl;
}

void CourseTree::displayTree() {

    cout << "\n===== UNIVERSITY TREE =====\n";

    for (int i = 0; i < faculties.size(); i++) {

        cout << "\nFaculty: "
             << faculties[i]->facultyName
             << endl;

        for (int j = 0;
             j < faculties[i]->departments.size();
             j++) {

            DepartmentNode* dept =
                faculties[i]->departments[j];

            cout << "  Department: "
                 << dept->deptName
                 << endl;

            for (int k = 0;
                 k < dept->courses.size();
                 k++) {

                CourseNode* course =
                    dept->courses[k];

                cout << "     "
                     << course->courseID
                     << " - "
                     << course->courseName
                     << " ("
                     << course->credits
                     << " credits)"
                     << endl;
            }
        }
    }
}

void CourseTree::preorderTraversal() {

    cout << "\n===== PREORDER =====\n";

    for (int i = 0; i < faculties.size(); i++) {

        cout << faculties[i]->facultyName << endl;

        for (int j = 0;
             j < faculties[i]->departments.size();
             j++) {

            DepartmentNode* dept =
                faculties[i]->departments[j];

            cout << "  " << dept->deptName << endl;

            for (int k = 0;
                 k < dept->courses.size();
                 k++) {

                cout << "    "
                     << dept->courses[k]->courseName
                     << endl;
            }
        }
    }
}

void CourseTree::postorderTraversal() {

    cout << "\n===== POSTORDER =====\n";

    for (int i = 0; i < faculties.size(); i++) {

        for (int j = 0;
             j < faculties[i]->departments.size();
             j++) {

            DepartmentNode* dept =
                faculties[i]->departments[j];

            for (int k = 0;
                 k < dept->courses.size();
                 k++) {

                cout << dept->courses[k]->courseName
                     << endl;
            }

            cout << dept->deptName << endl;
        }

        cout << faculties[i]->facultyName
             << endl;
    }
}
