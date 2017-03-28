

#include <iostream>
#include "Heap.h"

const int capacity = 100;



int main()
{
    Heap maxHeap (capacity);
    int j = 100;

    std::cout << "A maxHeap was created with capacity 100\n\n";
    std::cout << "Insert all even numbers from 0 to 99 into the heap.\n";
    for (int i = 0; i < j; i+=2)
    {
        maxHeap.insert(i);
    }
    std::cout << "Printing the maxHeap using << overloaded operator:\n";
    std::cout << maxHeap << "\n\n";


    std::cout << "Creating maxHeap2 (another Heap) using Copy Constructor, and Sort the Heap.\n";
    Heap maxHeap2 (maxHeap);
    maxHeap2.heapSort();
    std::cout << "Printing the maxHeap2 using << overloaded operator:\n";
    std::cout << maxHeap2 << "\n\n";


    std::cout << "Creating maxHeap3 (another Heap) by inserting all odd numbers from 0  to 100.\n";
    Heap maxHeap3 (capacity);
    for (int i = 1; i < j; i+=2)
    {
        maxHeap3.insert(i);
    }
    std::cout << "Printing the maxHeap3 using << overloaded operator:\n";
    std::cout << maxHeap3 << "\n\n";


    std::cout << "Creating maxHeap4 (another Heap) by adding 2 heaps: maxHeap4 = maxHeap + maxHeap3.\n";
    Heap maxHeap4 = maxHeap + maxHeap3;
    std::cout << "Printing the maxHeap4 using << overloaded operator:\n";
    std::cout << maxHeap4 << "\n\n";


    std::cout << "Creating maxHeap5 (another Heap) by heap assignment: maxHeap5 = maxHeap = maxHeap3.\n";
    Heap maxHeap5 = maxHeap = maxHeap3;
    std::cout << "Printing the maxHeap5 using << overloaded operator:\n";
    std::cout << maxHeap5 << "\n\n";


    std::cout << "Adding values to maxHeap5 by using operator +: maxHeap5 = maxHeap5 + 1000.\n";
    maxHeap5 = (maxHeap5 +  1000);
    std::cout << "Printing the maxHeap5 using << overloaded operator:\n";
    std::cout << maxHeap5 << "\n\n";


    std::cout << "Doubling  maxHeap5  by heap assignment: maxHeap5 += maxHeap5 += maxHeap4.\n";
    maxHeap5 += maxHeap5 += maxHeap4;
    std::cout << "Printing the maxHeap5 using << overloaded operator:\n";
    std::cout <<  maxHeap5 << "\n\n";



    std::cout << "Adding to maxHeap5  by heap assignment: (maxHeap5 += 2000) += 3000.\n";
    (maxHeap5 += 2000) += 3000;
    std::cout << "Printing the maxHeap5 using << overloaded operator:\n";
    std::cout <<  maxHeap5 << "\n\n";

    std::cout << "Sorting the maxHeap using extract max(), adjust(), heapSort().\n";
    maxHeap5.heapSort();
    std::cout << "Printing the maxHeap5 using << overloaded operator:\n";
    std::cout << maxHeap5 << "\n\n";


    std::cout<< "Printing the 10 th element by using the maxHeap5[10] ([] overloaded operator).\n";
    std::cout<< "maxHeap5[10] = " << maxHeap5[10] << std::endl;





    return 0;
}
