//=========================================================================
// Name        : menuFunctions.h
// Author      : John St Hilaire
// Version     : 1.0
// Last Updated : 2/25/23
// Description : header file for menu helper functions for Project 1 for CS300 at SNHU
//=========================================================================

#pragma once
#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

#include "BinarySearchTree.h"

bool LoadDataStructure(BinarySearchTree& bst, const std::string& filename);
bool DataStructureIsEmpty(const BinarySearchTree& bst);
void PrintCourseList(const BinarySearchTree& bst);
void PrintCourseInformation(const BinarySearchTree& bst, const std::string& courseID);
void ExitProgram();

#endif // MENUFUNCTIONS_H