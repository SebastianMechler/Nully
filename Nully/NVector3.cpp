#include "NVector3.h"

namespace Nully
{
  NVector3::NVector3()
    : x(0.0f),
      y(0.0f),
      z(0.0f)
  {
  }

  NVector3::NVector3(float a_x, float a_y, float a_z)
    : x(a_x),
      y(a_y),
      z(a_z)
  {
  }
}
