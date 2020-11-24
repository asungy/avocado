#include <string>

namespace py_interface {
    void Run();

    void Initialize();
    void Finalize();

    auto Execute(std::string module_name, std::string func_name) -> bool;
    void Call_Multiply(int val_a, int val_b);
}
