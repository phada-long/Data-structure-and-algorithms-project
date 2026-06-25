#ifndef TREE_H
#define TREE_H

#include <string>

class CourseTree {
public:
    void addFaculty(std::string facultyName);

    void addDepartment(std::string facultyName,
                       std::string deptName);

    void addCourse(std::string deptName,
                   std::string id,
                   std::string name,
                   int credits);

    void deleteDepartment(std::string deptName);
    void deleteCourse(std::string id);

    void searchCourse(std::string id);

    void displayTree();

    void preorderTraversal();
    void postorderTraversal();
};

#endif
