#include <string>

namespace py_interface {
    void run();

    void init();
    auto execute(std::string module_name, std::string func_name) -> bool;
}
