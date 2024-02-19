//============================================================================
// Name        : HashTable.cpp
// Author      : John Watson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

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

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (1): Initialize the structures used to hold bids
    nodes.resize(tableSize); // Initalize node structure by resizing tableSize
}

/*
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    this->tableSize = size;  // invoke local tableSize to size with this->
    nodes.resize(tableSize); // resize nodes size
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // Iterate over the vector
    for (int i = 0; i < this->tableSize; ++i) {
        Node* node = nodes[i].next; // Start with the second node in the list, if any
        // Traverse the linked list and delete the nodes
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp; // Only delete nodes created with new (i.e., the linked nodes)
        }
    }
}


/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (3): Implement logic to calculate a hash value
    return static_cast<unsigned int>(key) % tableSize; // return key % tableSize as unsigned int
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    unsigned int key = hash(stoi(bid.bidId)); // create the key for the given bid
    Node* node = &(nodes[key]); // retrieve node using key
    Node* prev = nullptr;

    if (node->key == UINT_MAX) {
        nodes[key] = Node(bid, key); // assign this node to the key position
    }
    else {
        while (node->next != nullptr) {
            node = node->next;
        }
        node->next = new Node(bid, key); // Append new node at the end of the chain
    }
}




/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // for node begin to end iterate
    for (int i = 0; i < this->tableSize; ++i) {
        Node* node = &(nodes[i]);
        if (node->key != UINT_MAX) { // if key not equal to UINT_MAx
            // output key, bidID, title, amount and fund
            cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
            // while next node not equal to nullptr
            while (node->next != nullptr) {
                node = node->next; // node is equal to next iter
                // output key, bidID, title, amount and fund
                cout << " -> " << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
            }
        }
    }
}


/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    unsigned int key = hash(stoi(bidId));
    Node* node = &(nodes[key]);
    Node* prev = nullptr;

    while (node != nullptr && node->key != UINT_MAX) {
        if (node->bid.bidId == bidId) {
            if (prev != nullptr) {  // If not the first node in the list
                prev->next = node->next; // Link previous node to the next node
                delete node; // Free the memory of the current node
                cout << "Bid removed." << endl;
                return; // Exit the function
            }
            else { // If it is the first node in the list
                if (node->next == nullptr) {
                    node->key = UINT_MAX; // Mark the node as unused
                    cout << "Bid removed." << endl;
                    return; // Exit the function
                }
                else {
                    // Move the first node of the list to the second node
                    Node* temp = node->next;
                    *node = *temp; // Copy the second node to the first node
                    delete temp; // Delete the old second node
                    cout << "Bid removed." << endl;
                    return; // Exit the function
                }
            }
        }
        prev = node; // Keep track of the previous node
        node = node->next; // Move to the next node in the list
    }
    cout << "Bid Id " << bidId << " not found." << endl;
}



/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    unsigned int key = hash(stoi(bidId)); // create the key for the given bid

    // attempt to find the bid at the hashed index
    Node* node = &(nodes[key]);

    // if the bucket is empty (key is UINT_MAX), the bid is not in the table
    if (node->key == UINT_MAX) {
        return bid; // return an empty bid
    }

    // while node not equal to nullptr
    while (node != nullptr) {
        // if the current node matches
        if (node->bid.bidId == bidId) {
            return node->bid; // return it the bid
        }
        node = node->next; // Move to the next node
    }

    // The bid was not found in the hash table
    return bid; //node is equal to next node
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
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
            hashTable->Insert(bid);
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
        //bidKey = "98109";
        bidKey = "98094";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv"; // smaller CSV
        //csvPath = "eBid_Monthly_Sales_Dec.csv"; // larger CSV
        // !old! bidKey = "98109";
        bidKey = "98094";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();

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
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

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
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
