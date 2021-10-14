
#include <Python.h>
#include <iostream>

PyObject* random(PyObject* self, PyObject* args)
{

    /* initialize random seed: */
    srand(time(NULL));
    int number=0;
    
    if (!PyArg_ParseTuple(args, "i", &number))
        return NULL;
    std::cout << "Randomizing" << std::endl;
    int random = number - rand() % 10;
    PyObject* python_val = Py_BuildValue("i",random);

    return python_val;

}



static PyMethodDef math_demo_methods[] = {
    {"random",(PyCFunction)random, METH_VARARGS,"Generate random number between 0-9"},
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef math_demo_module =
{
    PyModuleDef_HEAD_INIT,
    "math_demo", /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    math_demo_methods
};

PyMODINIT_FUNC PyInit_math_demo(void)

{

    return PyModule_Create(&math_demo_module);
}


