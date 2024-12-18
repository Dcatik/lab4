#pragma once
#include <iostream>
#include <vector>
#include <type_traits>

template <typename T, typename = void>
struct HasComparisonOperators : std::false_type {};

template <typename T>
struct HasComparisonOperators<T, std::enable_if_t<
	std::is_convertible<decltype(std::declval<T>() == std::declval<T>()), bool>::value&&
	std::is_convertible<decltype(std::declval<T>() < std::declval<T>()), bool>::value&&
	std::is_convertible<decltype(std::declval<T>() > std::declval<T>()), bool>::value
	>> : std::true_type {};

template <typename T>
class BinaryTree {
public:
	static_assert(HasComparisonOperators<T>::value, "Type T must have operators ==, <, and >.");

	/**
	 * @brief Default constructor. Returns an object with head value nullptr.
	*/
	BinaryTree();

	/**
	 * @brief Initiate object with start value.
	 * @param value Start value.
	*/
	BinaryTree(T value);

	/**
	 * @brief Copy constructor.
	 * @param other Object to be copied.
	*/
	BinaryTree(const BinaryTree& other);

	/**
	 * @brief The assignment operator for the BinaryTree class copies an object to another object.
	 * @param other Object of class BinaryTree
	 * @return Returns a reference to the object we assign.
	*/
	BinaryTree operator=(const BinaryTree& other);

	/**
	 * @brief Adds a new value to the binary tree.
	 * @param value Value to add.
	*/
	void Add(T value);

	/**
	 * @brief Adds new values to the binary tree.
	 * @param value Values to add.
	*/
	void Add(const std::vector<T>& values);

	/**
	 * @brief Removes a value from a binary tree.
	 * @param value Value to be removed.
	*/
	void Remove(T value);

	/**
	 * @brief Removes values from a binary tree.
	 * @param value Values to be removed.
	*/
	void Remove(const std::vector<T>& values);

	/**
	 * @brief Get the number of branches between its root and the deepest leaf node.
	 * @return Int number of branches between its root and the deepest leaf node.
	*/
	int GetHeight();

	/**
	 * @brief Get the minimum value of objects in a binary tree.
	 * @return Returns the minimum value of objects in a binary tree.
	*/
	T GetMinValue();

	/**
	 * @brief Get the maximum value of objects in a binary tree.
	 * @return Returns the maximum value of objects in a binary tree.
	*/
	T GetMaxValue();

	/**
	 * @brief Prints values of a binary tree on the console.
	*/
	void Display();

	/**
	 * @brief Draws a binary tree on the console.
	*/
	void Print();

	/**
	 * @brief Checks if objct in binary tree.
	 * @param value Object to find.
	 * @return True or false if not in tree.
	*/
	bool HasValue(T value);

	// def lab task func
	BinaryTree<T> ReturnSubTree(int less_than);

	std::vector<T> deepFirstSearch(T value);

	std::vector<T> breadthFirstSearch(T value);

	~BinaryTree();

private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node(T val) : data(val), left(nullptr), right(nullptr) {}
	};

	Node* head;

	Node* findMin(Node* node);
	Node* findMax(Node* node);

	void deleteTree(Node* node);
	Node* copyTree(const BinaryTree<T>& other);

	// def lab task helper func
	Node* returnSubTreeNode(Node* node, int less_than);

	void print(const std::string& prefix, const Node* node, bool isLeft);
};

#include "binarytree_impl.h"