#include <iostream>

#include "cli.hpp"
#include "python.hpp"
#include "influx.hpp"


int main( int argc, char * argv[] )
{
    return command::Run(argc, argv);
}
