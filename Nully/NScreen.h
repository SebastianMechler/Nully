#pragma once

#include "NTypes.h"

namespace Nully
{
  struct NScreenSize
  {
    nuint32 width;
    nuint32 height;

    NScreenSize(nuint32 a_width, nuint32 a_height)
    {
      width = a_width;
      height = a_height;
    }
  };

  class NScreen
  {
  public:
    void SetResolution(nuint32 a_width, nuint32 a_height);
    const NScreenSize& GetResolution() const;
    const nuint32& GetWidth() const;
    const nuint32& GetHeight() const;

    friend class NSingleton;

  private:
    NScreen();
    NScreenSize m_screenSize;
  };
}
