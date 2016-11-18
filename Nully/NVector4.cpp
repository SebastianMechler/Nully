#include "NVector4.h"

namespace Nully
{
  NVector4::NVector4()
    : x(0.0f),
      y(0.0f),
      z(0.0f),
      w(0.0f)
  {
  }
  NVector4::NVector4(float a_x, float a_y, float a_z, float a_w)
    : x(a_x),
      y(a_y),
      z(a_z),
      w(a_w)
  {
  }
}

