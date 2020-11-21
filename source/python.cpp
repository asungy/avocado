#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>

#include "python.hpp"

namespace py_interface {
    void init()
    {
        Py_Initialize();

        // Add current directory (of executable) to Python system path.
        // Required for importing relative Python modules.
        PyObject * py_path = PySys_GetObject((char *) "path");
        PyList_Append(py_path, PyUnicode_FromString("."));
    }

    void run() 
    {
        PyObject * module_name = PyUnicode_FromString("avotest");
        PyObject * py_module = PyImport_Import(module_name);

        if (py_module != nullptr)
        {
            std::cout << "Module found" << std::endl;
        }
        else
        {
            std::cout << "Module not found" << std::endl;
        }
    }
}
