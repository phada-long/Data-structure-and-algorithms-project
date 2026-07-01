#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

struct DepartmentNode {
    string department;
    DepartmentNode* left;
    DepartmentNode* right;
};

inline DepartmentNode* createDepartment(string dept) {
    DepartmentNode* node = new DepartmentNode();
    node->department = dept;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

inline DepartmentNode* insertDepartment(DepartmentNode* root, string dept) {

    if (root == nullptr)
        return createDepartment(dept);

    if (dept < root->department)
        root->left = insertDepartment(root->left, dept);
    else if (dept > root->department)
        root->right = insertDepartment(root->right, dept);

    return root;
}

inline void inorderDepartment(DepartmentNode* root) {

    if (root == nullptr)
        return;

    inorderDepartment(root->left);
    cout << root->department << endl;
    inorderDepartment(root->right);
}

inline DepartmentNode* searchDepartment(DepartmentNode* root, string dept) {

    if (root == nullptr)
        return nullptr;

    if (root->department == dept)
        return root;

    if (dept < root->department)
        return searchDepartment(root->left, dept);

    return searchDepartment(root->right, dept);
}

inline void buildDepartmentTree(
    DepartmentNode*& root,
    CourseList* list) {

    CourseElement* current = list->head;

    while (current != nullptr) {
        root = insertDepartment(root, current->data.department);
        current = current->next;
    }
}

#endif