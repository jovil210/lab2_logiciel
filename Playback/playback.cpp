// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#include "playback.h"
void DShowPlayer::OpenFile(PyObject* self, PyObject* args)
{
    IBaseFilter* pSource = NULL;
    PCWSTR pszFileName = L"Example.avi";

    // Create a new filter graph. (This also closes the old one, if any.)
    HRESULT hr = InitializeGraph();
    if (FAILED(hr))
    {
        goto done;
    }

    // Add the source filter to the graph.
    //hr = m_pGraph->AddSourceFilter(pszFileName, NULL, &pSource);
    //if (FAILED(hr))
    //{
    //    goto done;
    //}

    // Try to render the streams.
    hr = m_pGraph->RenderFile(pszFileName, NULL);

    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = Play();
        if (SUCCEEDED(hr))
        {
            // Wait for completion.
            long evCode;
            hr = VideoLoop();

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
    }

done:
    if (FAILED(hr))
    {
        TearDownGraph();;
    }
    SafeRelease(&pSource);
}



HRESULT DShowPlayer::Play()
{
    if (m_state != STATE_PAUSED && m_state != STATE_STOPPED)
    {
        return VFW_E_WRONG_STATE;
    }

    HRESULT hr = m_pControl->Run();
    if (SUCCEEDED(hr))
    {
        m_state = STATE_RUNNING;
    }
    return hr;
}

HRESULT DShowPlayer::Pause()
{
    if (m_state != STATE_RUNNING)
    {
        return VFW_E_WRONG_STATE;
    }

    HRESULT hr = m_pControl->Pause();
    if (SUCCEEDED(hr))
    {
        m_state = STATE_PAUSED;
    }
    return hr;
}

HRESULT DShowPlayer::Stop()
{
    if (m_state != STATE_RUNNING && m_state != STATE_PAUSED)
    {
        return VFW_E_WRONG_STATE;
    }

    HRESULT hr = m_pControl->Stop();
    if (SUCCEEDED(hr))
    {
        m_state = STATE_STOPPED;
    }
    return hr;
}

HRESULT DShowPlayer::InitializeGraph()
{

    TearDownGraph();
    // Create the Filter Graph Manager.
    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pGraph));
    if (FAILED(hr))
    {
        goto done;
    }

    hr = m_pGraph->QueryInterface(IID_PPV_ARGS(&m_pControl));
    if (FAILED(hr))
    {
        goto done;
    }

    hr = m_pGraph->QueryInterface(IID_PPV_ARGS(&m_pEvent));
    if (FAILED(hr))
    {
        goto done;
    }
    hr = m_pGraph->QueryInterface(IID_PPV_ARGS(&m_pSeek));
    if (FAILED(hr))
    {
        goto done;
    }
    m_state = STATE_STOPPED;

done:
    return hr;
}

void DShowPlayer::TearDownGraph()
{
    // Stop sending event messages
    if (m_pEvent)
    {
        m_pEvent->SetNotifyWindow((OAHWND)NULL, NULL, NULL);
    }

    SafeRelease(&m_pGraph);
    SafeRelease(&m_pControl);
    SafeRelease(&m_pEvent);
    SafeRelease(&m_pSeek);

    delete m_pVideo;
    m_pVideo = NULL;

    m_state = STATE_NO_GRAPH;
}


HRESULT DShowPlayer::VideoLoop() {
    HRESULT hr = NULL;
    double rate = 1.0;
    char entry = ' ';
    REFERENCE_TIME rt = 0 * ONE_SECOND;

    while (entry != 'Q' && entry != 'q')
    {
        entry = _getch();
        switch (entry)
        {
        case 'p':
        case 'P':
            if (m_state == STATE_RUNNING)
            {
                hr = Pause();
                std::cout << "Pausing video ... " << std::endl;
            }
            else if (m_state == STATE_PAUSED)
            {
                hr = Play();
                std::cout << "Resuming video ... " << std::endl;
            }
            break;
        case 'a':
        case 'A':
            if (rate < 4.0)
            {
                rate = rate + 0.25;
                hr = m_pSeek->SetRate(rate + 0.25);
            }
            else {
                rate = 1.0;
                hr = m_pSeek->SetRate(rate);
            }
            std::cout << "Rate: " << rate << std::endl;
            break;
        case 'r':
        case 'R':
            m_pSeek->SetPositions(&rt, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
            std::cout << "Restarting video ... " << std::endl;
            break;
        }

    }
    hr = Stop();
    std::cout << "Quitting ... " << std::endl;
    return hr;
}

static PyMethodDef Playback_methods[] = {
    {"OpenFile",(PyCFunction)OpenFile, METH_NOARGS,"Plays a video with the possibility of A: accelerate, P: Pause/Play, R: Restart or Q: Quit"},
    {NULL,NULL,0,NULL}
};
static struct PyModuleDef Playback_module =
{
    PyModuleDef_HEAD_INIT,
    "math_demo", /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    Playback_methods
};

PyMODINIT_FUNC PyInit_Playback(void)

{

    return PyModule_Create(&Playback_module);
}