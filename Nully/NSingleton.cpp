#include "NSingleton.h"

namespace Nully
{
  NSingleton::~NSingleton()
  {
    m_singleton = nullptr;
    m_shaderManager = nullptr;
    m_screen = nullptr;
  }
  void NSingleton::CreateInstance()
  {
    if (m_singleton == nullptr)
    {
      m_singleton = new NSingleton();
    }
  }
  NSingleton& NSingleton::GetInstance()
  {
    return *m_singleton;
  }
  void NSingleton::Release()
  {
    delete m_shaderManager;
    delete m_screen;

    // this needs to be the LAST cause it sets the pointers to nullptr!
    delete m_singleton;
  }

  NShaderManager& NSingleton::GetShaderManager()
  {
    return *m_shaderManager;
  }
  NScreen& NSingleton::GetScreen()
  {
    return *m_screen;
  }
  NSingleton::NSingleton()
  {
    m_singleton = this;
    m_shaderManager = new NShaderManager();
    m_screen = new NScreen();
  }

  NSingleton* NSingleton::m_singleton = nullptr;
  NShaderManager* NSingleton::m_shaderManager = nullptr;
  NScreen* NSingleton::m_screen = nullptr;
}