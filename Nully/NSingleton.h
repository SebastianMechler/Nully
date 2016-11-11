#pragma once

#include "NShaderManager.h"
#include "NScreen.h"
#include "NInput.h"

namespace Nully
{
  class NSingleton
  {
  public:
    ~NSingleton();
    static void CreateInstance();
    static NSingleton& GetInstance(); // could be deleted, cause getters for each Child is set
    static void Release();

    static NShaderManager& GetShaderManager();
    static NScreen& GetScreen();
    static IInput* GetInput();

  private:
    static NSingleton* m_singleton;

    // childmanagers
    static NShaderManager* m_shaderManager;
    static NScreen* m_screen;
    static IInput* m_input;

    NSingleton();
  };
}