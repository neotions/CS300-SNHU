//=========================================================================
// Name        : BinarySearchTree.cpp
// Author      : John St Hilaire
// Version     : 1.0
// Last Updated : 2/25/23
// Description : Menu helper functions for Project 1 for CS300 at SNHU
//=========================================================================


#include "BinarySearchTree.h"  // header for the BinarySearchTree class
#include <fstream>             // header for file stream operations
#include <sstream>             // header for string stream operations
#include <iostream>

// Function to load data from the file into the Binary Search Tree
bool LoadDataStructure(BinarySearchTree& bst, const std::string& filename) {
    std::ifstream file(filename); // open the file
    if (!file.is_open()) {
        return false; // return false if file can't be opened
    }

    std::string line;
    while (getline(file, line)) { // read each line from the file
        std::stringstream ss(line);
        std::string courseNumber, title;
        std::vector<std::string> prerequisites;

        getline(ss, courseNumber, ','); // get the course number
        getline(ss, title, ','); // get the title

        std::string prerequisite;
        while (getline(ss, prerequisite, ',')) { // get all prerequisites
            prerequisites.push_back(prerequisite);
        }

        Course course(courseNumber, title, prerequisites); // create a course object
        bst.insert(course); // insert the course into the BST
    }

    file.close(); // close the file
    return true; // return true if  successful
}

// Function to check if the Binary Search Tree is empty
bool DataStructureIsEmpty(const BinarySearchTree& bst) {
    return bst.isEmpty(); // call the isEmpty method of BST
}

// Function to print an alphanumerically ordered list of all courses
void PrintCourseList(const BinarySearchTree& bst) {
    bst.printAllCourses(); // call the printAllCourses method of BST
}

// Function to find and print the title and prerequisites of a course given its ID
void PrintCourseInformation(const BinarySearchTree& bst, const std::string& courseID) {
    bst.printCourse(courseID); // call the printcourse method of bst with the given course id
}

// Function to cleanly exit the program
void ExitProgram() {
    std::cout << "Exiting program.\n"; // print exiting message
}
