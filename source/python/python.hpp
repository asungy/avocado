#include "../data/data.hpp"

namespace py_interface {
    void Run();

    void Initialize();
    void Finalize();

    void Call_Multiply(int val_a, int val_b);
    stock::DataPoint GetFakeData(std::string symbol);
    void GetFakeList();
}
