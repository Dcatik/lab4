#pragma once

template <typename T>
class Container {                                       // Abstract class for linked lists
public:
    Container() = default;                              // define virtual default constructor
    ~Container() = default;                             // define virtual default destructor
    virtual T GetData() = 0;                            // define virtual method to get data
    virtual void Add(int index, const T& data) = 0;     // define virtual method to add data
    virtual void Remove(int index) = 0;                 // define virtual method to remove data
    virtual int Size() = 0;                             // define virtual method to get the size
    virtual T GetAt(int index) = 0;                     // define virtual method to get data at an index
    virtual T operator[](int index) = 0;                // define virtual method to get data at an index
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
    }
    Node* head;
};