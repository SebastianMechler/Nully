#include "NApplication.h"

namespace Nully
{
  NApplication::NApplication()
    : m_graphics(nullptr)
  {
  }

  NApplication::~NApplication()
  {
    if (m_graphics)
    {
      delete m_graphics;
      m_graphics = nullptr;
    }

    // release all singletons
    NSingleton::Release();
  }

  bool NApplication::Initialize(const NApplicationDesc& a_applicationDesc)
  {
    // Create all available singletons
    NSingleton::CreateInstance();
    NSingleton::GetScreen().SetResolution(a_applicationDesc.graphicsDesc.width, a_applicationDesc.graphicsDesc.height);

    // initialize window
    if (!m_window.Initialize(a_applicationDesc.windowDesc, NApplication::MessageHandling))
    {
      return false;
    }

    // set hwnd to graphicsDesc
    NGraphicsDesc graphicsDesc = a_applicationDesc.graphicsDesc;
    graphicsDesc.hwnd = m_window.GetWindowHandle();

    // initialize directX
    // if inittype == openGl ...
    // if inittype == directX ...
    m_graphics = new NDirectx();
    if (!m_graphics->Initialize(graphicsDesc))
    {
      return false;
    }
    
    // load shader
    if (!NSingleton::GetShaderManager().LoadShaderPool(reinterpret_cast<ID3D11Device*>(m_graphics->GetDevice())))
    {
      return false;
    }
    

    // load models


    return true;
  }
  void NApplication::Run()
  {
    MSG message = {};

    while (m_quit != true)
    {
      // Message Handling...
      while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0)
      {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }

      m_graphics->Clear();
      m_graphics->BeginDraw();
      m_graphics->Draw();
      m_graphics->EndDraw();


      Sleep(1);
    }
  }
  LRESULT NApplication::MessageHandling(HWND a_hwnd, UINT a_message, WPARAM a_wparam, LPARAM a_lparam)
  {
    switch (a_message)
    {
    case WM_DESTROY:
    case WM_QUIT:
    case WM_CLOSE:
      PostQuitMessage(0);
      NApplication::m_quit = true;
      break;

    case WM_KEYDOWN:
      // key down...
      break;

    case WM_KEYUP:
      // key up...
      break;
    }

    return DefWindowProc(a_hwnd, a_message, a_wparam, a_lparam);
  }

  bool NApplication::m_quit = false;
}

