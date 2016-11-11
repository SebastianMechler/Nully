#pragma once

#include <Windows.h>
#include <unordered_map>

#include "IInput.h"

namespace Nully
{
  class NInput : public IInput
  {
  public:
    ~NInput();

    // Keyboard
    bool GetKeyDown(const NKey a_key) override;
    bool GetKeyUp(const NKey a_key) override;
    void SetKeyDown(const NKey a_key) override;
    void SetKeyUp(const NKey a_key) override;

    // Mouse
    const NVector2& GetMousePositon() override;
    nuint32 GetMouseX() override;
    nuint32 GetMouseY() override;
    bool GetMouseButtonDown(const NMouseButton a_button) override;
    bool GetMouseButtonUp(const NMouseButton a_button) override;

    void SetMousePositon(nuint32 a_x, nuint32 a_y) override;
    void SetMouseButtonState(const nuint32 a_message) override;

    friend class NSingleton;

  private:
    NInput();
    NInput(const NInput&);
    std::unordered_map<NKey, bool> m_keyMap; // true = down, false = up
    std::unordered_map<NMouseButton, bool> m_mouseMap; // true = down, false = up
    NVector2 m_mousePosition; // x,y
  };
}