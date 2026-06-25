#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// ================= ACTION TYPES =================
enum ActionType {
    ADD_STUDENT,
    DELETE_STUDENT,
    UPDATE_GPA,
    ADD_COURSE,
    DROP_COURSE
};

// ================= ACTION STRUCT =================
struct Action {
    ActionType type;
    string data;   // store info like ID, name, GPA changes

    Action(ActionType t, string d) {
        type = t;
        data = d;
    }
};

// ================= UNDO STACK =================
class UndoStack {
private:
    stack<Action> history;

public:

    // ---------------- SAVE ACTION ----------------
    void pushAction(ActionType type, string data) {
        history.push(Action(type, data));
    }

    // ---------------- UNDO LAST ACTION ----------------
    void undo() {
        if (history.empty()) {
            cout << "No actions to undo.\n";
            return;
        }

        Action last = history.top();
        history.pop();

        cout << "\n[UNDO ACTION] ";

        switch (last.type) {

        case ADD_STUDENT:
            cout << "Remove added student -> " << last.data << endl;
            break;

        case DELETE_STUDENT:
            cout << "Restore deleted student -> " << last.data << endl;
            break;

        case UPDATE_GPA:
            cout << "Revert GPA change -> " << last.data << endl;
            break;

        case ADD_COURSE:
            cout << "Remove added course -> " << last.data << endl;
            break;

        case DROP_COURSE:
            cout << "Re-enroll dropped course -> " << last.data << endl;
            break;

        default:
            cout << "Unknown action\n";
            break;
        }
    }

    // ---------------- SHOW HISTORY ----------------
    void showHistory() {
        if (history.empty()) {
            cout << "No history available.\n";
            return;
        }

        stack<Action> temp = history;

        cout << "\n========== ACTION HISTORY ==========\n";

        while (!temp.empty()) {
            Action a = temp.top();
            temp.pop();

            switch (a.type) {

            case ADD_STUDENT:
                cout << "ADD_STUDENT: ";
                break;

            case DELETE_STUDENT:
                cout << "DELETE_STUDENT: ";
                break;

            case UPDATE_GPA:
                cout << "UPDATE_GPA: ";
                break;

            case ADD_COURSE:
                cout << "ADD_COURSE: ";
                break;

            case DROP_COURSE:
                cout << "DROP_COURSE: ";
                break;
            }

            cout << a.data << endl;
        }

        cout << "====================================\n";
    }
};

#endif