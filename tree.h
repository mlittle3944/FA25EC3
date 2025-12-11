//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H
#include <queue>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.

   DO NOT IMPLEMENT ANYTHING HERE.
   Only placeholders and TODO comments.
*/


template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    // TODO: Write constructor
    // Node(const string &nodeID, const U &value);
    Node(const string &nodeID, const U &value)
        : id(nodeID), data(value) {}
};

template <typename T>
class Tree {
private:
    Node<T>* root;
    void deleteSubtree(Node<T>* node) {
        // <-- ADD THIS
        if (!node) return;
        for (Node<T>* child : node->children) {
            deleteSubtree(child);
        }
        delete node;
    }
public:
    // TODO: Initialize root pointer to nullptr
    Tree() : root(nullptr) {}

    void createRoot(const string &id, const T &value){
        // TODO: Allocate memory, assign id, assign data, set as root
        if (root != nullptr) {
            cout << "Root already exists.\n";
            return;
        }
        root = new Node<T>(id, value);
    }

    void addNode(const string &parentID, const string &childID, const T &value){
        // TODO: Find parent, create child, link parent to child
        // TODO: Support repeated children under multiple parents

        Node<T>* parent = findNode(parentID);

        if (!parent) {
            cout << "Parent node not found: " << parentID << endl;
            return;
        }

        Node<T>* child = new Node<T>(childID, value);
        parent->children.push_back(child);
    }

    Node<T>* findNode(const string &id) {
    // TODO: Use DFS or BFS to search tree
    if (root == nullptr) return nullptr;

    queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* curr = q.front();
        q.pop();

        if (curr->id == id) return curr;

        for (Node<T>* child : curr->children)
            q.push(child);
    }
    return nullptr;
    }

    void printAll(){
        // TODO: Print entire structure in readable form
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }

        queue<pair<Node<T>*, size_t>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, level] = q.front();
            q.pop();

            // indent based on depth
            cout << string(level * 2, ' ')
                 << "- [" << node->id << "] " << node->data << endl;

            for (Node<T>* child : node->children)
                q.push({child, level + 1});
        }
    }


    void playGame() {
        if (!root) {
            cout << "No story loaded.\n";
            return;
        }

        Node<T>* current = root;
        while (true) {
            cout << "\n--- " << current->id << " ---\n";
            cout << current->data << "\n\n";

            if (current->children.empty()) {
                cout << "THE END.\n";
                break;
            }

            cout << "Choose your next path:\n";
            for (size_t i = 0; i < current->children.size(); i++)
                cout << "  " << (i + 1) << ") " << current->children[i]->id << "\n";

            int choice;
            cout << "Enter number: ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(current->children.size())) {
                cout << "Invalid choice. Try again.\n";
                continue;
            }

            current = current->children[choice - 1];
        }
    }


    ~Tree() {
        // TODO: Free all allocated memory
        deleteSubtree(root);
    }
};

#endif //FA25EC3_TREE_H
