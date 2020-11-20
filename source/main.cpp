
#include "ProjectVars.hpp"
#include "python.hpp"

#include <iostream>

int main( int argc, char * argv[] )
{
    std::cout << "Hello, Avocado!" << std::endl;

    std::cout << argv[0] << " Version: " << PROJECT_VERSION_MAJOR << "."
              << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH << std::endl;

    Python::run(argv[0]);

    return 0;
}
