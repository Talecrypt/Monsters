// File: tree.h
// Author: Saif Abu Hananah
// Date: 22/May/2025
// Monstertale - A Monster-Taming Game

#ifndef TREE_H
#define TREE_H

#include "Monsters.h"
#include <array>
#include <memory>
#include <string>
#include <iostream>

using namespace std;

// Node: represents a single 2-3-4 tree node.
class Node {
public:
    int numItems = 0;
    array<string,3> keys;
    array<unique_ptr<Monster>,3> data;
    array<Node*,4> children{nullptr,nullptr,nullptr,nullptr};
    Node* parent = nullptr;
    //Node Methods
    bool isLeaf() const;
    int findItem(const string& key) const;
    int insertItem(unique_ptr<Monster> m);
};

class Tree234 {
protected:
    Node* root = nullptr;
    // recursive helpers
    int insertRecursive(Node* current, unique_ptr<Monster> m);
    int split(Node* thisNode);
    int displayRecursive(Node* thisNode, int level);
    int removeAllRecursive(Node* thisNode);

public:
    //Constructor and Destructor
    Tree234();
    ~Tree234();
    // Public interface methods:
    int insert(unique_ptr<Monster> m);
    int display();
    int removeAll();
};

#endif
