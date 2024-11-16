#pragma once
#include "binarytree.h" 
#include <queue>
#include <stack>
#include <exception>
#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>

template <typename T>
BinaryTree<T>::BinaryTree() : head(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(T value) {
    head = new Node(value);
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) {
    head = copyTree(other.head);
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
    }
    else {
        addNode(head, value);
    }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMin(typename BinaryTree<T>::Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
void BinaryTree<T>::addNode(Node* node, T value) {
    if (value < node->data) {
        if (node->left) {
            addNode(node->left, value);
        }
        else {
            node->left = new Node(value);
        }
    }
    else {
        if (node->right) {
            addNode(node->right, value);
        }
        else {
            node->right = new Node(value);
        }
    }
}

template <typename T>
void BinaryTree<T>::Add(const std::vector<T>& values) {
    for (const T& value : values) {
        Add(value);
    }
}

template <typename T>
void BinaryTree<T>::Remove(T value) {
    head = removeRecursive(head, value);
}

template <typename T>
void BinaryTree<T>::Remove(const std::vector<T>& values) {
    for (int i = 0; i < values.size(); i++) {
        head = removeRecursive(head, values[i]);
    }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::removeRecursive(Node* node, T value) {
    if (!node) return nullptr;

    if (value < node->data) {
        node->left = removeRecursive(node->left, value);
    }
    else if (value > node->data) {
        node->right = removeRecursive(node->right, value);
    }
    else {
        if (!node->left) {
            Node* rightChild = node->right;
            delete node;
            return rightChild;
        }
        else if (!node->right) {
            Node* leftChild = node->left;
            delete node;
            return leftChild;
        }
        else {
            Node* minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = removeRecursive(node->right, minNode->data);
        }
    }
    return node;
}

template <typename T>
T BinaryTree<T>::GetMinValue() {
    Node* minNode = findMin(head);
    return minNode ? minNode->data : T();
}

template <typename T>
T BinaryTree<T>::GetMaxValue() {
    Node* node = head;
    while (node && node->right) {
        node = node->right;
    }
    return node ? node->data : T();
}

template <typename T>
int BinaryTree<T>::GetHeight() {
    return calculateHeight(head);
}

template <typename T>
int BinaryTree<T>::calculateHeight(Node* node) {
    if (!node) return 0;

    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);

    if (leftHeight > rightHeight) {
        return 1 + leftHeight;
    }
    else {
        return 1 + rightHeight;
    }
}


template <typename T>
void BinaryTree<T>::Display() {
    displayInOrder(head);
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::displayInOrder(Node* node) {
    if (node) {
        displayInOrder(node->left);
        std::cout << node->data << " ";
        displayInOrder(node->right);
    }
}

template <typename T>
bool BinaryTree<T>::HasValue(T value) {
    return searchValue(head, value);
}

template <typename T>
void BinaryTree<T>::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    deleteTree(head);
}

template <typename T>
bool BinaryTree<T>::searchValue(typename BinaryTree<T>::Node* node, T value) {
    try {
        T found = deepFirstSearch(value);
        return true;
    }
    catch (std::exception ex){
        return false;
    }
}

template <typename T>
T BinaryTree<T>::deepFirstSearch(T value) {
    std::stack<Node*> stack;
    stack.push(head);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        if (current->data == value) {
            return current->data;
        }

        if (current->right) {
            stack.push(current->right);
        }

        if (current->left) {
            stack.push(current->left);
        }
    }

    throw std::runtime_error("Value not found");
}

template <typename T>
T BinaryTree<T>::breadthFirstSearch(T value) {
    std::queue<Node*> queue;
    queue.push(head);

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();

        if (current->data == value) {
            return current->data;
        }

        if (current->left) {
            queue.push(current->left);
        }
        if (current->right) {
            queue.push(current->right);
        }
    }

    throw std::runtime_error("Value not found");
}

template <typename T>
void BinaryTree<T>::Print() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    print(L"", head, false);
}

template <typename T>
void BinaryTree<T>::print(const std::wstring& prefix, const Node* node, bool isLeft) {
    if (node != nullptr) {
        std::wcout << prefix;

        std::wcout << (isLeft ? L"├──" : L"└──");

        std::wcout << node->data << std::endl;

        print(prefix + (isLeft ? L"│   " : L"    "), node->left, true);
        print(prefix + (isLeft ? L"│   " : L"    "), node->right, false);
    }
}


