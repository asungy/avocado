#include <iostream>

#include "command.hpp"
#include "python.hpp"


int main( int argc, char * argv[] )
{
    // py_interface::Run();
    command::Run(argc, argv);

    return 0;
}
