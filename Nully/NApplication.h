#pragma once

#include <Windows.h>

#include "NIntern.h"
#include "NSingleton.h"
#include "NWindow.h"
#include "NApplicationDesc.h"
#include "NDirectx.h"

namespace Nully
{
  class NApplication
  {
  public:
    NApplication();
    ~NApplication();
    bool Initialize(const NApplicationDesc& a_windowDesc);
    void Run();
    static LRESULT CALLBACK MessageHandling(HWND a_hwnd, UINT a_message, WPARAM a_wparam, LPARAM a_lparam);

  private:
    static bool m_quit;
    NWindow m_window;

    IGraphics* m_graphics;
  };
}