#include "spdlog/spdlog.h"

#include "cli.hpp"
#include "python.hpp"
#include "influx.hpp"

#include <iostream>


int main( int argc, char * argv[] )
{
    spdlog::info("Welcome to spdlog!");
    return command::Run(argc, argv);
}
