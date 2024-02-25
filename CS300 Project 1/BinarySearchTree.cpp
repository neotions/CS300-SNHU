//=========================================================================
// Name        : BinarySearchTree.cpp
// Author      : John St Hilaire
// Version     : 1.0
// Last Updated : 2/25/23
// Description : Binary Search Tree class implementation for Project 1 for CS300 at SNHU
//=========================================================================

#include "BinarySearchTree.h"

// Insert a new course into the BST.
TreeNode* BinarySearchTree::insertCourse(TreeNode* node, Course newCourse) {
    // if the current node is null, create a new treenode with the course
    if (node == nullptr) {
        return new TreeNode(newCourse);
    }
    // if the course number is less than the current node's, insert to the left
    if (newCourse.courseNumber < node->course.courseNumber) {
        node->left = insertCourse(node->left, newCourse);
    }
    // if the course number is greater than the current node's, insert to the right
    else if (newCourse.courseNumber > node->course.courseNumber) {
        node->right = insertCourse(node->right, newCourse);
    }

    return node; // return the node pointer
}

// Print course details.
void BinarySearchTree::printCourseDetails(TreeNode* node) const {
    if (node == nullptr) return; // if the node is null, return
    std::cout << "\nCourse Number: " << node->course.courseNumber << std::endl; // output the course number
    std::cout << "Title: " << node->course.title << std::endl; // output the course title
    std::cout << "Prerequisites: "; // handle the prerequisites list
    if (node->course.prerequisites.empty()) { // if there are no prerequisites, print 'none'
        std::cout << "None\n";
    }
    else { // else print each prerequisite
        for (const std::string& prereq : node->course.prerequisites) {
            std::cout << prereq << " ";
        }
    }
    std::cout << std::endl; // end the line after printing prerequisites
}

// In-order traversal to print all courses.
void BinarySearchTree::inOrderTraversal(TreeNode* node) const {
    if (node == nullptr) return; // if the current node is null, return to the previous level of recursion
    inOrderTraversal(node->left); // visit the left subtree
    std::cout << node->course.courseNumber << ", " << node->course.title << std::endl; // print info on individual course
    inOrderTraversal(node->right); // visit the right subtree
}

// Find a course by course number.
TreeNode* BinarySearchTree::findCourse(TreeNode* node, const std::string& courseNumber) const {
    
    std::string courseNum = toUpperCase(courseNumber); // convert the input course number to uppercase


    if (node == nullptr || node->course.courseNumber == courseNum) { // if the node is null or the node's course number matches the search term, return the node
        return node;
    }

    if (courseNum < node->course.courseNumber) { // if the search term is less than the node's course number, search in the left subtree
        return findCourse(node->left, courseNum);
    }
    else { // if the search term is greater than the node's course number, search in the right subtree
        return findCourse(node->right, courseNum);
    }
}

// Helper function to convert a string to uppercase for case-insensitive comparison
// source: cppreference.com/std/algorithm/transform
std::string BinarySearchTree::toUpperCase(const std::string& str) const {
    std::string upperStr;
    upperStr.reserve(str.length()); // reserve memory to avoid reallocations
    std::transform(str.begin(), str.end(), std::back_inserter(upperStr), ::toupper); // convert each character in the string to uppercase
    return upperStr; // return the uppercase string
}

//  Recursively delete all nodes.
void BinarySearchTree::deleteAllNodes(TreeNode* node) {
    if (node) { // check if the current node exists
        deleteAllNodes(node->left); // recursively delete all nodes in the left subtree
        deleteAllNodes(node->right); // recursively delete all nodes in the right subtree
        delete node; // delete the current node after its children have been deleted
    }
}

// Constructor.
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

// Check if the tree is empty.
bool BinarySearchTree::isEmpty() const {
    return root == nullptr; // return true if root is null, indicating the tree has no nodes
}

// Insert a new course into the BST.
void BinarySearchTree::insert(Course newCourse) {
    root = insertCourse(root, newCourse); // call the insertCourse helper function, starting at the root, to insert the new course
}

// Print details of a single course.
void BinarySearchTree::printCourse(const std::string& courseNumber) const {
    TreeNode* courseNode = findCourse(root, courseNumber); // find the course in the bst using the findcourse helper function
    if (courseNode != nullptr) { // if the course was found, print its details
        printCourseDetails(courseNode);
    }
    else { // if the course was not found, print a message indicating so
        std::cout << "Course not found." << std::endl;
    }
}



// Print all courses in the BST.
void BinarySearchTree::printAllCourses() const {
    if (isEmpty()) { // check if the bst is empty before trying to print
        std::cout << "The tree is empty." << std::endl;
        return;
    }
    std::cout << std::endl;
    inOrderTraversal(root); // perform an in-order traversal to print all courses
    std::cout << std::endl;
}

// Destructor.
BinarySearchTree::~BinarySearchTree() {
    deleteAllNodes(root); // call the deleteallnodes helper function to delete all nodes starting from the root
}
