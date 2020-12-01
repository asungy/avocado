#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>

#include "python.hpp"


namespace py_interface {
    void Run()
    {
        Initialize();
        GetFakeList();
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

    void Call_Multiply(int val_a, int val_b)
    {
        PyObject * pystr = PyUnicode_FromString("market_data");
        PyObject * py_module = PyImport_Import(pystr);
        Py_DECREF(pystr);

        if (py_module != nullptr)
        {
            std::cout << "Module found" << std::endl;
            PyObject * func = PyObject_GetAttrString(py_module, "multiply");
            if (func != nullptr)
            {
                PyObject * pArgs = PyTuple_New(2);

                PyObject * pVal1 = PyLong_FromLong(val_a);
                PyObject * pVal2 = PyLong_FromLong(val_b);

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
    }

    stock::DataPoint GetFakeData(std::string symbol)
    {
        PyObject * pystr = PyUnicode_FromString("market_data");
        PyObject * py_module = PyImport_Import(pystr);
        Py_DECREF(pystr);

        if (py_module != nullptr)
        {
            std::cout << "Module found" << std::endl;
            PyObject * func = PyObject_GetAttrString(py_module, "get_fake_data");
            if (func != nullptr)
            {
                PyObject * pArgs = PyTuple_New(1);
                PyObject * pVal = PyUnicode_FromString(symbol.c_str());
                PyTuple_SetItem(pArgs, 0, pVal);

                PyObject * result = PyObject_CallObject(func, pArgs);
                
                PyObject * py_symbol = PyUnicode_AsEncodedString(PyDict_GetItemString(result, "symbol"), "utf-8", "strict");

                stock::DataPoint pt{ 
                    PyBytes_AS_STRING(py_symbol),
                    PyFloat_AsDouble(PyDict_GetItemString(result, "open")),
                    PyFloat_AsDouble(PyDict_GetItemString(result, "high")),
                    PyFloat_AsDouble(PyDict_GetItemString(result, "low")),
                    PyFloat_AsDouble(PyDict_GetItemString(result, "close")),
                    0 // timestamp
                };

                Py_DECREF(result);

                return pt;
            }
        }

        throw std::runtime_error("pymodule market_data could not be found");
    }

    void GetFakeList()
    {
        PyObject * pystr = PyUnicode_FromString("market_data");
        PyObject * py_module = PyImport_Import(pystr);
        Py_DECREF(pystr);

        if (py_module != nullptr)
        {
            std::cout << "Module found" << std::endl;
            PyObject * func = PyObject_GetAttrString(py_module, "get_data_list");
            if (func != nullptr)
            {
                PyObject * pArgs = PyTuple_New(2);
                PyObject * pVal1 = PyUnicode_FromString("MSFT");
                PyObject * pVal2 = PyLong_FromLong(10);
                PyTuple_SetItem(pArgs, 0, pVal1);
                PyTuple_SetItem(pArgs, 1, pVal2);

                PyObject * result = PyObject_CallObject(func, pArgs);
                Py_DECREF(func);
                
                for (int i = 0; i < 10; ++i)
                {
                    PyObject * item = PyList_GetItem(result, i);

                    PyObject * symbol = PyUnicode_AsEncodedString(PyDict_GetItemString(item, "symbol"), "utf-8", "strict");
                    std::cout << "symbol: " << PyBytes_AS_STRING(symbol) << std::endl
                              << "open: " << PyFloat_AsDouble(PyDict_GetItemString(item, "open")) << std::endl
                              << "high: " << PyFloat_AsDouble(PyDict_GetItemString(item, "high")) << std::endl
                              << "low: " << PyFloat_AsDouble(PyDict_GetItemString(item, "low")) << std::endl
                              << "close: " << PyFloat_AsDouble(PyDict_GetItemString(item, "close")) << std::endl
                              << "volume: " << PyLong_AsLong(PyDict_GetItemString(item, "volume")) << std::endl << std::endl;
                }

                Py_DECREF(result);
            }
        }
        else
        {
            std::cout << "Module not found" << std::endl;
        }
    }
}
