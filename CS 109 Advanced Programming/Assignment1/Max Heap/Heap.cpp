



#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>

#include "Heap.h"





void Heap::adjust (int i)
{
    int l = 2*i;
    int r = l+1;
    int largest = 0;
    if((l <= Nel) && (array[l] > array[i]))
        largest = l;
    else
        largest = i;
    if((r <= Nel) && (array[r] > array[largest]))
        largest = r;

    if (largest != i)
    {
        std::swap(array[i], array[largest]);
        adjust(largest);
    }



}





Heap::Heap()
{
    array = nullptr;
    Nel = 0;
}





Heap::Heap(int MSize):MaxSize(MSize)
{
    array = (int*) calloc(MaxSize+1 , sizeof(int));
    if(!array)
    {
        std::cout << "mem failure, exiting \n";
        exit(EXIT_FAILURE);
    }
    Nel = 0;
}






Heap::Heap(const Heap& newHeap)
{

    MaxSize = newHeap.MaxSize;
    Nel = newHeap.Nel;
    array =(int*) calloc(newHeap.MaxSize+1 , sizeof(int));
    if(!array)
    {
        std::cout << "mem failure, exiting \n";
        exit(EXIT_FAILURE);
    }
    std::copy(newHeap.array, newHeap.array + newHeap.Nel+1, array);


}



Heap Heap::makeCopy(const Heap& newHeap)
{
    Heap temp;
    temp.MaxSize = newHeap.MaxSize;
    temp.Nel = newHeap.Nel;
    temp.array =(int*) calloc(newHeap.MaxSize+1 , sizeof(int));
    if(!temp.array)
    {
        std::cout << "mem failure, exiting \n";
        exit(EXIT_FAILURE);
    }
    std::copy(newHeap.array, newHeap.array + newHeap.Nel+1, temp.array);

    return temp;
}






Heap& Heap::operator =(const Heap& otherHeap)
{
    if( this  != &otherHeap)
    {
        if(array != nullptr)
        {
            free (array);
            array = nullptr;
        }
        array = (int*) calloc(MaxSize+1 , sizeof(int));
        if(!array)
        {
            std::cout << "mem failure, exiting \n";
            exit(EXIT_FAILURE);
        }

        MaxSize = otherHeap.MaxSize +1;
        Nel = otherHeap.Nel;
        std::copy(otherHeap.array, otherHeap.array + otherHeap.Nel+1, array);

    }
    return *this;
}



bool Heap::insert (int item)
{
    int i = ++Nel;
    if ( i == MaxSize)
    {
        std::cout << "heap size exceeded" << std::endl;
        return false;
    }
    while ( (i > 1 ) && ( array[i/2] < item ))
    {
        array[i] = array[i/2];
        i/=2;
    }
    array[i] = item;
    return true;
}







bool Heap::delMax(int & item)
{

    if ( !Nel)
    {
        std::cout << "heap is empty" << std::endl ;
        return false;
    }
    item = array[1];
    array [1] = array[Nel--];
    adjust (1);
    return true;
}






bool Heap::isEmpty()
{
    if (array == nullptr)
    {
        return true;
    }
    return false;
}




void Heap::printHeap()
{
    if (isEmpty())
    {
        std::cout << "Heap is empty!\n";

    }



    std::cout << "[ ";
    for (int i = 1; i <= Nel ; i++)
    {
        std::cout << array [i] << " ";
    }
    std::cout << "]\n";


}





void Heap::heapSort()
{
    int k = Nel;
    int value = 0;
    int* tempArray = (int*) calloc(MaxSize+1 , sizeof(int));
    if(!tempArray)
    {
        std::cout << "mem failure, exiting \n";
        exit(EXIT_FAILURE);
    }

    if (!isEmpty())
    {
        for(int i = 1; i <= k; i++)
        {
            delMax(value);
            tempArray[i] = value;


        }
        Nel = k;
        array = tempArray;


    }

    else
        std::cout << "Heap is empty\n";
}





int Heap::getNel()
{
    return Nel;
}





int Heap::getElement(int position)
{
    if(position > 0 && position <= Nel)
    {
        return array[position];
    }
    return -1;
}


int Heap::getMaxSize()
{
    return MaxSize;
}


void Heap::setMaxSize(int value)
{
    MaxSize = value;
}






Heap::~Heap()
{
    Nel = 0;
    if ( array != nullptr)
    {
        free (array);
        array = nullptr;
    }

}





Heap& Heap::operator +=(Heap& otherHeap)
{

    Heap temp;
    if(this == &otherHeap)
    {
        temp = makeCopy(otherHeap);
    }
    else
    {
        temp = otherHeap;
    }


    MaxSize += temp.MaxSize + 1 ;
    for(int i = 1; i <= temp.Nel; i++)
    {
        insert(temp[i]);
    }

    return *this;

}


Heap& Heap::operator += (int value)
{

    MaxSize ++ ;
    insert(value);
    return *this;
}

int Heap::operator[](int position)
{
    heapSort();
    return getElement(position);

}




std::ostream& operator <<(std::ostream& outputStream, Heap& myHeap)
{

    if (myHeap.isEmpty())
    {
        outputStream << "Heap is empty!\n";

    }

    outputStream << "[ ";
    for (int i = 1; i <= myHeap.getNel() ; i++)
    {
        outputStream << myHeap.getElement(i) << " ";
    }
    outputStream<< "]\n";

    return outputStream;

}



Heap  operator +  (Heap& otherHeap, int value)
{
    Heap temp (otherHeap);
    temp.insert(value);
    return temp;
}



const Heap  operator + ( Heap& first, Heap& second)
{
    Heap temp(first.getMaxSize() + second.getMaxSize() + 2);

    for(int i = 1; i <= first.getNel(); i++)
    {
        temp.insert(first.getElement(i));
    }

    for(int i = 1; i <= second.getNel(); i++)
    {
        temp.insert(second.getElement(i));
    }



    return temp;
}



