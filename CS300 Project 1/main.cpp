//==============================================================
// Name        : main.cpp
// Author      : John St Hilaire
// Version     : 1.0
// Last Updated : 2/25/23
// Description : Main C++ file for Project 1 for CS300 at SNHU
//==============================================================


#include <iostream> // for user interaction
#include <string> // for string type
#include "BinarySearchTree.h" // for Binary Search Tree Class
#include "menuFunctions.h"  // for functions called by menu



// Main Menu
int main() {

    BinarySearchTree* dataStructure = new BinarySearchTree(); // create a new binary search tree instance

    // display until the user decides to exit
    while (true) {
        std::cout << "Welcome to the course planner.\n\n";
        std::cout << "1. Load Data Structure\n";
        std::cout << "2. Print Courses List\n";
        std::cout << "3. Print Course.\n";
        std::cout << "4. Exit\n\n";

        std::string choice;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        // load data structure
        if (choice == "1") {
            std::string filename;
            std::cout << "Enter filename (default is courses.csv): ";
            std::cin >> filename;
            bool success = LoadDataStructure(*dataStructure, filename);
            if (success) {
                std::cout << "Data loaded successfully.\n\n";
            }
            else {
                std::cout << "Failed to load data.\n";
            }
        }

        // print course information in alphanumeric order
        else if (choice == "2") {
            if (!DataStructureIsEmpty(*dataStructure)) {
                PrintCourseList(*dataStructure);
            }
            else {
                std::cout << "Data structure is empty. Load data first.\n";
            }
        }

        // print info on individual course
        else if (choice == "3") {
            if (!DataStructureIsEmpty(*dataStructure)) {
                std::string courseID;
                std::cout << "Enter course ID: ";
                std::cin >> courseID;
                PrintCourseInformation(*dataStructure, courseID);
            }
            else {
                std::cout << "Data structure is empty. Load data first.\n";
            }
        }

        // exit program and clean memory
        else if (choice == "4") {
            ExitProgram();
            break;  // exit the while loop
        }
        else { // handle invalid menu options
            std::cout << choice << " is not a valid option." << std::endl;
        }
    }

    delete dataStructure; // cleanup before exiting the program

    return 0;  // indicate successful program termination
}


