// File: tree.cpp
// Author: Saif Abu Hananah
// Date: 22/May/2025
// Monstertale - A Monster-Taming Game

#include "tree.h"
#include <iostream>

using namespace std;

// Constructor and Destructor
Tree234::Tree234() : root(nullptr) {}
Tree234::~Tree234() { removeAll(); }

// Public insert: split root if full, then recurse
int Tree234::insert(unique_ptr<Monster> m) {
    if (!root) {
        root = new Node();
        root->insertItem(move(m));
        return 0;
    }
    if (root->numItems == 3) {
        split(root);
    }
    return insertRecursive(root, move(m));
}

// Recursive insert helper
int Tree234::insertRecursive(Node* current, unique_ptr<Monster> m) {
    if (current->isLeaf()) {
        if (current->numItems == 3) {
            split(current);
            return insertRecursive(current->parent, move(m));
        } else {
            current->insertItem(move(m));
            return 0;
        }
    }
    string key = m->getName();
    int idx = 0;
    while (idx < current->numItems && key > current->keys[idx]) idx++;
    Node* child = current->children[idx];
    if (child->numItems == 3) {
        split(child);
        idx = 0;
        while (idx < current->numItems && key > current->keys[idx]) idx++;
    }
    return insertRecursive(current->children[idx], move(m));
}
// Splits a full 4-item node into two 2-item nodes and promotes the middle key/data int the parent
int Tree234::split(Node* thisNode) {
    Node* parent = thisNode->parent;
    //Create a new right sibling node and move the 3rd key/data into it
    Node* right = new Node();
    right->keys[0] = thisNode->keys[2];
    right->data[0] = move(thisNode->data[2]);
    right->numItems = 1;
    //If thisNode is not a leaf, reassign its 3rd & 4th children to the new right node
    if (!thisNode->isLeaf()) {
        right->children[0] = thisNode->children[2];
        right->children[1] = thisNode->children[3];
        if (right->children[0]) right->children[0]->parent = right;
        if (right->children[1]) right->children[1]->parent = right;
    }
    //Shrink thisNode down to a 2-item node by resetting numItems
    thisNode->numItems = 1;
    //Extract the middle item (index 1) for promotion
    unique_ptr<Monster> promoData = move(thisNode->data[1]);
    string promoKey = thisNode->keys[1];
    thisNode->data[1].reset();
    //If not a leaf, null out the now-unused child pointers
    if (!thisNode->isLeaf()) {
        thisNode->children[2] = nullptr;
        thisNode->children[3] = nullptr;
    }
    //If splitting the root (no parent), create a new root node
    if (!parent) {
        parent = new Node();
        root = parent;
        parent->children[0] = thisNode;
        thisNode->parent = parent;
    }
    //Find thisNode’s index in its parent’s child array
    int idx = 0;
    while (parent->children[idx] != thisNode) idx++;
   //Shift parent’s keys, data, and children right of idx to make room 
    for (int i = parent->numItems; i > idx; --i) {
        parent->keys[i] = parent->keys[i-1];
        parent->data[i] = move(parent->data[i-1]);
        parent->children[i+1] = parent->children[i];
    }
    //Insert the promoted key/data and attach the new right node
    parent->keys[idx] = promoKey;
    parent->data[idx] = move(promoData);
    parent->children[idx+1] = right;
    right->parent = parent;
    parent->numItems++;
    return 0;
}

// Public display
int Tree234::display() {
    if (!root) return -1;
    displayRecursive(root, 0);
    return 0;
}

int Tree234::displayRecursive(Node* node, int level) {
    if (!node) return -1;
    for (int i = 0; i < node->numItems; ++i) {
        displayRecursive(node->children[i], level + 1);
        for (int j = 0; j < level; ++j) {
            cout << "  " << node->keys[i] << endl;
        }
    }
    displayRecursive(node->children[node->numItems], level + 1);
    return 0;
}

// Remove all nodes
int Tree234::removeAll() {
    if (!root) return -1;
    removeAllRecursive(root);
    root = nullptr;
    return 0;
}

// Recursive removal
int Tree234::removeAllRecursive(Node* node) {
    if (!node) return -1;
    for (int i = 0; i <= node->numItems; ++i)
        removeAllRecursive(node->children[i]);
    delete node;
    return 0;
}

// Node helpers
int Node::findItem(const string& key) const {
    for (int i = 0; i < numItems; ++i)
        if (keys[i] == key) return i;
    return -1;
}

// Inserts a new Monster into this node in sorted order by its name.
int Node::insertItem(unique_ptr<Monster> m) {
    string key = m->getName();
    int i = numItems - 1;
    while (i >= 0 && keys[i] > key) {
        keys[i+1] = keys[i];
        data[i+1] = move(data[i]);
        children[i+2] = children[i+1];
        i--;
    }
    keys[i+1] = key;
    data[i+1] = move(m);
    children[i+2] = nullptr;
    numItems++;
    return i+1;
}

// Returns true if this node has no children (i.e., children[0] is nullptr).
bool Node::isLeaf() const { return children[0] == nullptr; }
