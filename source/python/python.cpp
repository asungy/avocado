#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>

#include "python.hpp"


namespace py_interface {
    void run()
    {
        init();
        execute("market_data", "test");
    }

    void init()
    {
        Py_Initialize();

        // Add current directory (of executable) to Python system path.
        // Required for importing relative Python modules.
        PyObject * py_path = PySys_GetObject((char *) "path");
        PyList_Append(py_path, PyUnicode_FromString("."));
    }

    auto execute(std::string module_name, std::string func_name) -> bool
    {
        PyObject * pystr = PyUnicode_FromString(module_name.c_str());
        PyObject * py_module = PyImport_Import(pystr);
        Py_DECREF(pystr);

        if (py_module != nullptr)
        {
            std::cout << "Module found" << std::endl;
        }
        else
        {
            std::cout << "Module not found" << std::endl;
        }

        return true;
    }
}
