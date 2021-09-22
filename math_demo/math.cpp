
#include <Python.h>


PyObject* random(PyObject* self, PyObject* args)
{

    /* initialize random seed: */

    srand(time(NULL));

    int random = rand() % 10;

    PyObject* python_val = Py_BuildValue("i", random);

    return python_val;

}



static PyMethodDef math_demo_methods[] = {
    {"random",(PyCFunction)random, METH_NOARGS,"Generate random number betweeen 0-9"},
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


