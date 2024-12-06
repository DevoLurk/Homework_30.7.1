#include <iostream>
#include "intArray.h"

using namespace std;

#define SIZE 10000000

int main()
{
    IntArray myarray(SIZE);

    myarray.fillArray();
    //myarray.printArray();
    std::cout << "\n--------------------------------" << std::endl;
    myarray.QsortNoThreads();
    //myarray.printArray();

    

    myarray.fillArray();
    //myarray.printArray();
    std::cout << "\n--------------------------------" << std::endl;
    myarray.QsortThreads();
    //myarray.printArray();

    myarray.fillArray();
    //myarray.printArray();
    std::cout << "\n--------------------------------" << std::endl;
    myarray.QsortThreadsPool();
    //myarray.printArray();
    std::cout << "\n--------------------------------" << std::endl;


    return 0;
}