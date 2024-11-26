#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "binarytree.h"

template <typename T>
BinaryTree<T>::BinaryTree() : head(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(T value) {
    head = new Node(value);
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) {
    head = copyTree(other);
}

template <typename T>
BinaryTree<T> BinaryTree<T>::operator=(const BinaryTree& other) {
    if (this != &other) {
        deleteTree(head);
        head = copyTree(other.head);
    }
    return *this;
}

template <typename T>
void BinaryTree<T>::Add(T value) {
    if (!head) {
        head = new Node(value);
        return;
    }

    Node* current = head;
    while (true) {
        if (value < current->data) {
            if (!current->left) {
                current->left = new Node(value);
                break;
            }
            current = current->left;
        }
        else {
            if (!current->right) {
                current->right = new Node(value);
                break;
            }
            current = current->right;
        }
    }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMin(Node* node) {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMax(Node* node) {
    if (!node) return nullptr;
    while (node->right) {
        node = node->right;
    }
    return node;
}

template <typename T>
void BinaryTree<T>::Add(const std::vector<T>& values) {
    for (const T& value : values) {
        Add(value);
    }
}

template <typename T>
void BinaryTree<T>::Remove(T value) {
    Node* parent = nullptr;
    Node* current = head;

    while (current && current->data != value) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (!current) return;

    if (!current->left || !current->right) {
        Node* child = current->left ? current->left : current->right;
        if (!parent) {
            head = child;
        }
        else if (parent->left == current) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        delete current;
    }
    else {
        Node* successorParent = current;
        Node* successor = current->right;

        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }

        current->data = successor->data;

        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        }
        else {
            successorParent->right = successor->right;
        }
        delete successor;
    }
}

template <typename T>
T BinaryTree<T>::GetMinValue() {
    Node* minNode = findMin(head);
    return minNode ? minNode->data : T();
}

template <typename T>
T BinaryTree<T>::GetMaxValue() {
    Node* maxNode = findMax(head);
    return maxNode ? maxNode->data : T();
}

template <typename T>
int BinaryTree<T>::GetHeight() {
    if (!head) return 0;

    int height = 0;
    std::vector<Node*> currentLevel{ head };

    while (!currentLevel.empty()) {
        std::vector<Node*> nextLevel;
        for (Node* node : currentLevel) {
            if (node->left) nextLevel.push_back(node->left);
            if (node->right) nextLevel.push_back(node->right);
        }
        currentLevel = nextLevel;
        ++height;
    }

    return height;
}

template <typename T>
void BinaryTree<T>::Display() {
    if (!head) return;

    std::vector<Node*> stack;
    Node* current = head;

    while (!stack.empty() || current) {
        while (current) {
            stack.push_back(current);
            current = current->left;
        }
        current = stack.back();
        stack.pop_back();

        std::cout << current->data << " ";
        current = current->right;
    }
    std::cout << std::endl;
}

template <typename T>
bool BinaryTree<T>::HasValue(T value) {
    try {
        if (deepFirstSearch(value) != std::vector<T>(0)) {
            return true;
        }
        return false;
    }
    catch (std::exception ex) {
        std::cout << (ex.what()) << std::endl;
        return false;
    }
}

template <typename T>
void BinaryTree<T>::deleteTree(Node* node) {
    if (!node) return;

    std::vector<Node*> nodes{ node };

    while (!nodes.empty()) {
        Node* current = nodes.back();
        nodes.pop_back();

        if (current->left) nodes.push_back(current->left);
        if (current->right) nodes.push_back(current->right);

        delete current;
    }
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    deleteTree(head);
}


template <typename T>
void BinaryTree<T>::Remove(const std::vector<T>& values) {
    for (const T& value : values) {
        Remove(value);
    }
}

template <typename T>
std::vector<T> BinaryTree<T>::deepFirstSearch(T value) {
    if (!head) {
        throw std::runtime_error("Tree is empty");
    }

    std::vector<T> result;

    std::stack<Node*> stack;
    std::vector<T> path;

    stack.push(head);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        path.push_back(current->data);

        if (current->data == value) {
            for (const T& val : path) {
                result.push_back(val);
            }
            return result;
        }

        if (current->right) {
            stack.push(current->right);
        }
        if (current->left) {
            stack.push(current->left);
        }
    }

    std::cout << std::endl;
    return std::vector<T>(0);
}



template <typename T>
std::vector<T> BinaryTree<T>::breadthFirstSearch(T value) {
    if (!head) throw std::runtime_error("Tree is empty");
    std::vector<T> result;

    std::vector<Node*> currentLevel{ head };
    while (!currentLevel.empty()) {
        std::vector<Node*> nextLevel;

        for (Node* node : currentLevel) {
            if (node->data == value) {
                result.push_back(node->data);
                return result;
            }
            result.push_back(node->data);

            if (node->left) nextLevel.push_back(node->left);
            if (node->right) nextLevel.push_back(node->right);
        }

        currentLevel = nextLevel;
    }
    return std::vector<T>(0);
}

template <typename T>
void BinaryTree<T>::Print() {
    if (!head) {
        std::cout << "(empty tree)" << std::endl;
        return;
    }

    print("", head, false);
}

template <typename T>
void BinaryTree<T>::print(const std::string& prefix, const Node* node, bool isLeft) {
    if (!node) return;

    struct PrintState {
        const Node* node;
        std::string prefix;
        bool isLeft;
    };

    std::vector<PrintState> stack;
    stack.push_back({ node, prefix, isLeft });

    while (!stack.empty()) {
        PrintState current = stack.back();
        stack.pop_back();

        const Node* currentNode = current.node;

        std::cout << current.prefix;
        std::cout << (current.isLeft ? "|--" : "`--");
        std::cout << currentNode->data << std::endl;

        if (currentNode->right) {
            stack.push_back({ currentNode->right, current.prefix + (current.isLeft ? "|   " : "    "), false });
        }

        if (currentNode->left) {
            stack.push_back({ currentNode->left, current.prefix + (current.isLeft ? "|   " : "    "), true });
        }
    }
}
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyTree(const BinaryTree<T>& other) {
    if (!other.head) {
        return nullptr;
    }

    Node* newRoot = new Node(other.head->data);

    struct CopyState {
        Node* originalNode;
        Node* copyNode;
    };

    std::vector<CopyState> stack;
    stack.push_back({ other.head, newRoot });

    while (!stack.empty()) {
        CopyState current = stack.back();
        stack.pop_back();

        Node* originalNode = current.originalNode;
        Node* copyNode = current.copyNode;

        if (originalNode->left) {
            copyNode->left = new Node(originalNode->left->data);
            stack.push_back({ originalNode->left, copyNode->left });
        }

        if (originalNode->right) {
            copyNode->right = new Node(originalNode->right->data);
            stack.push_back({ originalNode->right, copyNode->right });
        }
    }

    return newRoot;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::returnSubTreeNode(Node* node, int less_than) {
    if (!node) return nullptr;

    if (node->data >= less_than) {
        return returnSubTreeNode(node->left, less_than);
    }

    Node* newNode = new Node(node->data);
    newNode->left = returnSubTreeNode(node->left, less_than);
    newNode->right = returnSubTreeNode(node->right, less_than);
    return newNode;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::ReturnSubTree(int less_than) {
    BinaryTree<T> subtree;
    subtree.head = returnSubTreeNode(head, less_than);
    return subtree;
}
