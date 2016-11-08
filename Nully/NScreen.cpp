#include "NScreen.h"

namespace Nully
{
  NScreen::NScreen()
    : m_screenSize(0, 0)
  {
  }
  void NScreen::SetResolution(nuint32 a_width, nuint32 a_height)
  {
    m_screenSize.width = a_width;
    m_screenSize.height = a_height;
  }
  const NScreenSize& NScreen::GetResolution() const
  {
    return m_screenSize;
  }
  const nuint32& NScreen::GetWidth() const
  {
    return m_screenSize.width;
  }
  const nuint32& NScreen::GetHeight() const
  {
    return m_screenSize.height;
  }
}
