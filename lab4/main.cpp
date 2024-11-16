#include <iostream>
#include "BinaryTree.h"
#include <exception>

int main() {
    BinaryTree<int> tree(10);

    // Add single values to the tree
    tree.Add(5);
    tree.Add(15);
    tree.Add(2);
    tree.Add(8);
    tree.Add(12);
    tree.Add(18);

    std::cout << "Binary tree in-order traversal:" << std::endl;
    tree.Display();
    tree.Print();

    std::vector<int> values = { 3, 7, 11, 20, 54, 324, 54, 1, 2, 3 };
    tree.Add(values);

    std::cout << "\nBinary tree after adding multiple values:" << std::endl;
    tree.Display();
    tree.Print();

    std::cout << "\nMinimum value in the tree: " << tree.GetMinValue() << std::endl;
    std::cout << "Maximum value in the tree: " << tree.GetMaxValue() << std::endl;

    std::cout << "Height of the tree: " << tree.GetHeight() << std::endl;

    std::cout << "Does the tree contain the value 7? " << (tree.HasValue(7) ? "Yes" : "No") << std::endl;
    std::cout << "Does the tree contain the value 21? " << (tree.HasValue(21) ? "Yes" : "No") << std::endl;

    tree.Remove(10);
    std::cout << "\nBinary tree after removing the value 10:" << std::endl;
    tree.Display();

    tree.Remove(std::vector<int> {7, 11});
    std::cout << "\nBinary tree after removing the value 7, 11:" << std::endl;
    tree.Display();

    return 0;
}
