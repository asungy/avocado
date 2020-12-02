#pragma once

#include "../data/data.hpp"

namespace py_interface {
    // Used for development purposes
    void Run();

    // Initializes Python interpreter and adds pymodules to import path.
    void Initialize();

    // Calls Py_Finalize to clean up Python interpreter.
    void Finalize();

    // Gets fake market data from pymodules
    stock::DataPoint GetFakeData(std::string symbol);
    void GetFakeList();
}
