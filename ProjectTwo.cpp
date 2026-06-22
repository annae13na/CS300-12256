//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Anna Fuentes
// Version     : 1.0
// Copyright   : © 2026 Anna Fuentes
// Description : CS 300 Project Two - Course Planner using a Binary Search Tree
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;
    void InOrder(Node* node);

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void Insert(Course course);
    void PrintCourseList();
    void PrintCourse(string courseNumber);
};

void BinarySearchTree::Insert(Course course) {

    Node* newNode = new Node(course);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;

    while (current != nullptr) {
        if (course.courseNumber < current->course.courseNumber) {
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

void BinarySearchTree::PrintCourseList() {
    cout << "Here is a sample schedule:" << endl;
    InOrder(root);
}

void BinarySearchTree::InOrder(Node* node) {

    if (node == nullptr) {
        return;
    }

    InOrder(node->left);

    cout << node->course.courseNumber
         << ", "
         << node->course.courseTitle
         << endl;

    InOrder(node->right);
}

void BinarySearchTree::PrintCourse(string courseNumber) {

    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber == courseNumber) {

            cout << current->course.courseNumber << ", "
                 << current->course.courseTitle << endl;

            cout << "Prerequisites: ";

            if (current->course.prerequisites.empty()) {
                cout << "None";
            }
            else {
                for (unsigned int i = 0; i < current->course.prerequisites.size(); i++) {
                    cout << current->course.prerequisites[i];

                    if (i < current->course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
            }

            cout << endl;
            return;
        }

        if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    cout << "Course not found." << endl;
}

void loadCourses(string fileName, BinarySearchTree& bst) {
	ifstream file(fileName);

	if (!file.is_open()) {
	    file.open("../" + fileName);
	}

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid course format." << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        for (unsigned int i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }

        bst.Insert(course);
    }

    file.close();

    cout << "Data loaded successfully." << endl;
}

int main() {

	BinarySearchTree bst;

    cout << "Welcome to the course planner." << endl;

    int choice = 0;

    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        switch (choice) {

        case 1:
            loadCourses("courses.csv", bst);
            break;

        case 2:
            bst.PrintCourseList();
            break;

        case 3:
        {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            bst.PrintCourse(courseNumber);
            break;
        }

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
