#ifndef HEAP_H
#define HEAP_H


#include <iostream>
#include <cstdlib>

class Heap
{
private:
    int * array;          // Pointer to integer array
    int MaxSize;          // Total capacity of the MaxHeap
    int Nel;              // Number of elements in the MaxHeap , Nel <= MaxSize
    void adjust (int i);  // Heapify functions, function that keep the properties of the Max Heap

public:
    Heap();                   // Default Constructor
    Heap(int MSize);          // Constructor taking MaxCapacity as parameter
    Heap(const Heap& newHeap);// Copy Constructor
    virtual ~Heap();          // Destructor


    int getNel();                 // Get the number of elements in the MaxHeap
    int getMaxSize();             // Get the capacity (MaxSize) of  the MaxHeap
    int getElement(int position); // Get the element in the MaxHeap at position
    void setMaxSize(int value);   // Set the capacity (MaxSize) of the MaxHeap to a new value
    bool isEmpty();               // Check if the MaxHeap is empty
    bool insert (int item);       // Insert a new element into MaxHeap
    bool delMax(int & item);      // Delete the Max Element by saving in the parameter &item
    void printHeap();             // Print the contents of the MaxHeap
    void heapSort();              // Sorting the heap ascending order
    Heap makeCopy(const Heap& other); // Helper function, making a copy of the heap


    Heap& operator = (const Heap& otherHeap);     // = operator overloaded Heap1 = Heap2
    Heap& operator +=(Heap& otherHeap);
    Heap& operator +=(int value);           // += operator overloaded Heap1 += Heap2
    int operator[](int position);                 // [] operator overloaded cout << Heap1[10]


    friend Heap operator + (Heap& other ,int value); // operator overloading Heap1 = Heap2 + 100
};

const Heap operator + (Heap& first,Heap& second); // + operator overloaded Heap1 = Heap2 + Heap3                // + operator overloaded Heap1 = heap2 + 10;                //
std::ostream& operator <<(std::ostream& outputStream, Heap& myHeap);//  << operator overloaded cout << Heap1



#endif // HEAP_H
