#pragma once

#include <unordered_map>

#include "IInput.h"

namespace Nully
{
  class NInput : public IInput
  {
  public:
    NInput();
    ~NInput();

    bool GetKeyDown(const NKey a_key);
    bool GetKeyUp(const NKey a_key);
    void SetKeyDown(const NKey a_key);
    void SetKeyUp(const NKey a_key);

  private:
    std::unordered_map<NKey, bool> m_keyMap; // true = down, false = up
  };
}