#pragma comment(lib, "Strmiids.lib")
#include "playback.h"
#include <Python.h>


PyObject* play_video(PyObject* self, PyObject* args)
{
    DShowPlayer* g_pPlayer = new DShowPlayer();

    // Initialize the COM library.
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return new PyObject;
    }

    char* entry;
    // Parsing entry of python function
    if (!PyArg_ParseTuple(args, "s", &entry))
        return NULL;

    // char* to wchar_t* conversion
    size_t cSize = strlen(entry)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs_s(&cSize, wc, cSize, entry, cSize);

    //IMPORTANT: Change this string to a file on your system.
    hr = g_pPlayer->OpenFile(wc);

    CoUninitialize();

    return new PyObject;
}

// Creating Python module methods
static PyMethodDef Playback_methods[] = {
    {"play_video",(PyCFunction)play_video, METH_VARARGS,"Play Video with possibility of A: Accelerate, P: Pause/Play, Q: Quit, R: Restart"},
    {NULL,NULL,0,NULL}
};

//Creating Python module
static struct PyModuleDef Playback_module =
{
    PyModuleDef_HEAD_INIT,
    "Playback", /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    Playback_methods
};


// Initializing module
PyMODINIT_FUNC PyInit_Playback(void)

{

    return PyModule_Create(&Playback_module);
}



