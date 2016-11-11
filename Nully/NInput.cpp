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
}

