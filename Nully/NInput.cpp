#include "NInput.h"

namespace Nully
{
  NInput::NInput()
  {
  }

  NInput::~NInput()
  {
  }

  bool NInput::GetKeyDown(const NKey a_key)
  {
    return (m_keyMap[a_key] == true);
  }

  bool NInput::GetKeyUp(const NKey a_key)
  {
    return (m_keyMap[a_key] == false);
  }

  void NInput::SetKeyDown(const NKey a_key)
  {
    m_keyMap[a_key] = true;
  }

  void NInput::SetKeyUp(const NKey a_key)
  {
    m_keyMap[a_key] = false;
  }
  const NVector2& NInput::GetMousePositon()
  {
    return m_mousePosition;
  }
  nuint32 NInput::GetMouseX()
  {
    return static_cast<nuint32>(m_mousePosition.x);
  }
  nuint32 NInput::GetMouseY()
  {
    return static_cast<nuint32>(m_mousePosition.y);
  }
  bool NInput::GetMouseButtonDown(const NMouseButton a_button)
  {
    return (m_mouseMap[a_button] == true);
  }
  bool NInput::GetMouseButtonUp(const NMouseButton a_button)
  {
    return (m_mouseMap[a_button] == false);
  }
  void NInput::SetMousePositon(nuint32 a_x, nuint32 a_y)
  {
    m_mousePosition.x = static_cast<float>(a_x);
    m_mousePosition.y = static_cast<float>(a_y);
  }
  void NInput::SetMouseButtonState(const nuint32 a_message)
  {
    switch (a_message)
    {
    default:
    case WM_LBUTTONDOWN:
      m_mouseMap[NMouseButton::Left] = true;
      break;

    case WM_RBUTTONDOWN:
      m_mouseMap[NMouseButton::Right] = true;
      break;

    case WM_MBUTTONDOWN:
      m_mouseMap[NMouseButton::Middle] = true;
      break;

    case WM_LBUTTONUP:
      m_mouseMap[NMouseButton::Left] = false;
      break;

    case WM_RBUTTONUP:
      m_mouseMap[NMouseButton::Right] = false;
      break;

    case WM_MBUTTONUP:
      m_mouseMap[NMouseButton::Middle] = false;
      break;
    }
  }
}

