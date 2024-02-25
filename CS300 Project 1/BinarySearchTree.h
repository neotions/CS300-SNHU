//==========================================================================================
// Name        : BinarySearchTree.h
// Author      : John St Hilaire
// Version     : 1.0
// Last Updated : 2/25/23
// Description : Header file for Binary Search Tree class for Project 1 for CS300 at SNHU
//==========================================================================================

#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // For std::transform
#include <cctype>    // For std::toupper


// course structure to hold course data
struct Course {
    std::string courseNumber;
    std::string title;
    std::vector<std::string> prerequisites;

    // constructor for the Course structure
    Course(std::string num, std::string tit, std::vector<std::string> prereqs)
        : courseNumber(num), title(tit), prerequisites(prereqs) {}
};

// TreeNode structure for the Binary Search Tree
struct TreeNode {
    Course course;
    TreeNode* left;
    TreeNode* right;

    // constructor for the TreeNode structure
    TreeNode(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// BinarySearchTree class
class BinarySearchTree {
private:
    TreeNode* root;

    // helper methods
    TreeNode* insertCourse(TreeNode* node, Course newCourse);
    void printCourseDetails(TreeNode* node) const;
    void inOrderTraversal(TreeNode* node) const;
    void deleteAllNodes(TreeNode* node);
    std::string toUpperCase(const std::string& str) const;

    TreeNode* findCourse(TreeNode* node, const std::string& courseNumber) const;

public:
    BinarySearchTree(); // constructor
    ~BinarySearchTree(); // destructor
    void insert(Course newCourse);
    bool isEmpty() const;
    void printCourse(const std::string& courseNumber) const;
    void printAllCourses() const;

    // additional methods can be declared here
};

#endif // BINARYSEARCHTREE_H
