#pragma once
#pragma comment(lib, "Strmiids.lib")
#include <new>
#include <windows.h>
#include <dshow.h>
#include <conio.h>
#include <iostream>
#include <Python.h>
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


class CVideoRenderer;

#define ONE_SECOND 10000000

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

enum PlaybackState
{
    STATE_NO_GRAPH,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED,
};

const UINT WM_GRAPH_EVENT = WM_APP + 1;

typedef void (CALLBACK* GraphEventFN)(HWND hwnd, long eventCode, LONG_PTR param1, LONG_PTR param2);

class DShowPlayer
{
public:
    DShowPlayer();
    ~DShowPlayer();

    PlaybackState State() const { return m_state; }

    void OpenFile(PyObject* self, PyObject* args);

    HRESULT Play();
    HRESULT Pause();
    HRESULT Stop();

    //BOOL    HasVideo() const;
    //HRESULT UpdateVideoWindow(const LPRECT prc);
    //HRESULT Repaint(HDC hdc);
    //HRESULT DisplayModeChanged();

    //HRESULT HandleGraphEvent(GraphEventFN pfnOnGraphEvent);

private:
    HRESULT InitializeGraph();
    void    TearDownGraph();
    //HRESULT CreateVideoRenderer();
    //HRESULT RenderStreams(IBaseFilter* pSource);
    HRESULT VideoLoop();
    PlaybackState   m_state;

    // Video window. This window also receives graph events.

    IGraphBuilder* m_pGraph;
    IMediaControl* m_pControl;
    IMediaEventEx* m_pEvent;
    IMediaSeeking* m_pSeek;
    CVideoRenderer* m_pVideo;
};