#include <iostream>
#include <exception>
#include "BinaryTree.h"

int main() {
    BinaryTree<int> tree(10);
    BinaryTree<int> tree2(tree);

    tree.Add(5);
    tree.Add(15);
    tree.Add(2);
    tree.Add(8);
    tree.Add(12);
    tree.Add(18);

    std::cout << "Find breadthly '18': " << std::endl;
    std::vector<int> bfs = tree.breadthFirstSearch(18);
    if (bfs != std::vector<int>(0)) {
        std::cout << "Found" << std::endl;
    }
    for (int i = 0; i < bfs.size(); i++) {
        std::cout << bfs[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Find deeply: " << std::endl;
    std::vector<int> dfs = tree.deepFirstSearch(18);
    if (dfs != std::vector<int>(0)) {
        std::cout << "Found" << std::endl;
    }
    for (int i = 0; i < dfs.size(); i++) {
        std::cout << dfs[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Binary tree in-order traversal:" << std::endl;
    tree.Display();
    tree.Print();
    tree2.Display();

    std::vector<int> values = { 3, 7, 11, 20, 54, 324, 54, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    tree.Add(values);

    std::cout << "\nBinary tree after adding multiple values:" << std::endl;
    tree.Display();
    tree.Print();

    std::cout << "All values less 7: " << std::endl;
    BinaryTree<int> subtree = tree.ReturnSubTree(7);
    subtree.Print();

    std::cout << "\nMinimum value in the tree: " << tree.GetMinValue() << std::endl;
    std::cout << "Maximum value in the tree: " << tree.GetMaxValue() << std::endl;

    std::cout << "Height of the tree: " << tree.GetHeight() << std::endl;

    std::cout << "Does the tree contain the value 7? " << (tree.HasValue(7) ? "Yes" : "No") << std::endl;
    std::cout << "Does the tree contain the value 21? " << (tree.HasValue(21) ? "Yes" : "No") << std::endl;

    tree.Remove(10);
    std::cout << "\nBinary tree after removing the value 10:" << std::endl;
    tree.Display();
    tree.Print();

    tree.Remove(std::vector<int> {7, 11});
    std::cout << "\nBinary tree after removing the value 7, 11:" << std::endl;
    tree.Display();
    tree.Print();

    return 0;
}