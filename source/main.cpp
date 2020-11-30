#include <iostream>

#include "command.hpp"
#include "python.hpp"
#include "influx.hpp"


int main( int argc, char * argv[] )
{
    // command::Run(argc, argv);
    influx::Run();
    return 0;
}
