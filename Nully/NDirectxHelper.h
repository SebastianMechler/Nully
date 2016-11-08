#pragma once

#include <Windows.h>

namespace Nully
{
  bool NDirectXFailed(HRESULT a_result);

  template<typename T> void NSafeRelease(T*& aInterface)
  {
    if (aInterface != nullptr)
    {
      aInterface->Release();
      aInterface = nullptr;
    }
  }
}
