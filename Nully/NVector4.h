#pragma once

namespace Nully
{
  class NVector4
  {
  public:
    NVector4();
    NVector4(float a_x, float a_y, float a_z, float a_w);

    float x, y, z, w;
  };
}