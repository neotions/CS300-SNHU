//============================================================================
// Name        : BinarySearchTree_New.cpp
// Author      : John St Hilaire
// Version     : 1.0
// Copyright   : Copyright � 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================



// forward declarations
double strToDouble(string str, char ch);

// Function to determine if str1 is lexicographically less than str2
bool strLessThan(string str1, string str2) {
    return str1 < str2;
}


// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
        Node() {
        bid = aBid;
    }
};


void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    void DeleteAll(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    root = nullptr; //root is equal to nullptr
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    DeleteAll(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    inOrder(root); // call inOrder fuction and pass root 
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    postOrder(root);// postOrder root
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    preOrder(root);// preOrder root
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (5) Implement inserting a bid into the tree
 
    // if root equarl to null ptr
    if (root == nullptr) {
        root = new Node(bid); // root is equal to new node bid
    } 
    else {
        addNode(root, bid); // add Node root and bid
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    root = removeNode(root, bidId);
}


/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (7) Implement searching the tree for a bid
    // set current node equal to root

    // keep looping downwards until bottom reached or matching bidId found
        // if match found, return current bid

        // if bid is smaller than current node then traverse left
        // else larger so traverse right

    Node* current = root;
    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            return current->bid; // Bid found
        }
        //current = current->bid.bidId > bidId ? current->left : current->right; // Traverse left or right
        current = strLessThan(bidId,current->bid.bidId) ? current->left : current->right; // Traverse left or right
    }

    Bid bid;
    return bid;
}

void BinarySearchTree::DeleteAll(Node* node) {
    if (node != nullptr) {
        DeleteAll(node->left);
        DeleteAll(node->right);
        delete node;
    }
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (8) Implement inserting a bid into the tree
    
    // if node is larger then add to left
    //if (node->bid.amount > bid.amount) {
    if (strLessThan(bid.bidId,node->bid.bidId)) {
        if (node->left == nullptr) {
            node->left = new Node(bid); // this node becomes left
        }
        else {
            addNode(node->left, bid); // else recurse down the left node
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid); // this node becomes right
        }
        else {
            addNode(node->right, bid); // else recurse down the right node
        }
    }
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    if (node == nullptr) {
        return node;
    }

    // traverse the tree to find the node
    if (strLessThan(bidId, node->bid.bidId)) {
        node->left = removeNode(node->left, bidId);
    }
    else if (strLessThan(node->bid.bidId, bidId)) {
        node->right = removeNode(node->right, bidId);
    }
    else {
        // remove node if found

        // case 1: no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        // case 2: one child
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // case 3: two children
        // find the inorder successor
        Node* temp = node->right;
        while (temp && temp->left != nullptr) {
            temp = temp->left;
        }

        // copy the inorder successor's content to this node
        node->bid = temp->bid;

        // delete the inorder successor
        node->right = removeNode(node->right, temp->bid.bidId);
    }
    return node;
}


void BinarySearchTree::inOrder(Node* node) {
    // FixMe (9): Pre order root
    //if node is not equal to null ptr
    //InOrder not left
    //output bidID, title, amount, fund
    //InOder right
    if (node != nullptr) {
        inOrder(node->left); // Visit left child
        displayBid(node->bid); // Visit node itself
        inOrder(node->right); // Visit right child
    }
}
void BinarySearchTree::postOrder(Node* node) {
    // FixMe (10): Pre order root
    //if node is not equal to null ptr
    //postOrder left
    //postOrder right
    //output bidID, title, amount, fund
    if (node != nullptr) {
        postOrder(node->left); // visit left child
        postOrder(node->right); // visit right child
        displayBid(node->bid); // visit node itself
    }
}

void BinarySearchTree::preOrder(Node* node) {
    // FixMe (11): Pre order root
    //if node is not equal to null ptr
    //output bidID, title, amount, fund
    //postOrder left
    //postOrder right
    if (node != nullptr) {
        displayBid(node->bid); // visit node itself
        preOrder(node->left); // visit left child
        preOrder(node->right); // visit right child
    }
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info

void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}
*/

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98085";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98085";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
