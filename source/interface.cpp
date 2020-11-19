#include "interface.hpp"

namespace Python {
    void run(char * argv) 
    {
        wchar_t *program = Py_DecodeLocale(argv, NULL);
        if (program == NULL) {
            fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
            exit(1);
        }
        Py_SetProgramName(program);  /* optional but recommended */
        Py_Initialize();
        PyRun_SimpleString("from time import time,ctime\n"
                           "print('Today is', ctime(time()))\n");
        if (Py_FinalizeEx() < 0) {
            exit(120);
        }
        PyMem_RawFree(program);
    }
}
