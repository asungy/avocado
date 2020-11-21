#include "python.hpp"

#include <iostream>

int main( int argc, char * argv[] )
{
    py_interface::init();
    py_interface::run();

    return 0;
}
