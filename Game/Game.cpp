#include <iostream>


void main()
{
    void* obj;

    obj = (void*)"esto es un obj";

    std::cout << (char*)obj << std::endl;

    obj = (void*)4;

    std::cout << (int)obj << std::endl;

    obj = (void*)'O';

    std::cout << (char)obj << std::endl;

}