#pragma once

#include "NKey.h"
#include "NVector2.h"
#include "NMouseButton.h"
#include "NTypes.h"

namespace Nully
{
  class IInput
  {
  public:
    virtual bool GetKeyDown(const NKey a_key) = 0;
    virtual bool GetKeyUp(const NKey a_key) = 0;
    virtual void SetKeyDown(const NKey a_key) = 0;
    virtual void SetKeyUp(const NKey a_key) = 0;

    virtual const NVector2& GetMousePositon() = 0;
    virtual nuint32 GetMouseX() = 0;
    virtual nuint32 GetMouseY() = 0;
    virtual bool GetMouseButtonDown(const NMouseButton a_button) = 0;
    virtual bool GetMouseButtonUp(const NMouseButton a_button) = 0;
    virtual void SetMousePositon(nuint32 a_x, nuint32 a_y) = 0;
    virtual void SetMouseButtonState(const nuint32 a_message) = 0;

    virtual ~IInput() {};
  };
}
