#include <iostream>
#include<cilk/hyperobject_base.h>
int main() {
    std::cout << "Hello, World!" << std::endl;
    cilk::hyperobject< Bag<int> > succbag();

}



