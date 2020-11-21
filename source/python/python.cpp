#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>

#include "python.hpp"


namespace py_interface {
    void Run()
    {
        Initialize();
        Execute("market_data.maths", "multiply");
        Finalize();
    }

    void Initialize()
    {
        Py_Initialize();

        // Add pymodules to Python system path.
        //
        // Required for importing relative Python modules.
        PyObject * py_path = PySys_GetObject((char *) "path");
        PyList_Append(py_path, PyUnicode_FromString("./pymodules"));
    }

    void Finalize()
    {
        Py_Finalize();
    }

    auto Execute(std::string module_name, std::string func_name) -> bool
    {
        PyObject * pystr = PyUnicode_FromString(module_name.c_str());
        PyObject * py_module = PyImport_Import(pystr);
        Py_DECREF(pystr);

        if (py_module != nullptr)
        {
            std::cout << "Module found" << std::endl;
            PyObject * func = PyObject_GetAttrString(py_module, func_name.c_str());
            if (func != nullptr)
            {
                PyObject * pArgs = PyTuple_New(2);

                PyObject * pVal1 = PyLong_FromLong(6);
                PyObject * pVal2 = PyLong_FromLong(4);

                PyTuple_SetItem(pArgs, 0, pVal1);
                PyTuple_SetItem(pArgs, 1, pVal2);

                PyObject * result = PyObject_CallObject(func, pArgs);
                std::cout << "Result: " << PyLong_AsLong(result) << std::endl;
            }
        }
        else
        {
            std::cout << "Module not found" << std::endl;
        }

        return true;
    }
}
