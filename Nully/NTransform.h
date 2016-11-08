#pragma once

#include "NVector3.h"

namespace Nully
{
  class NTransform
  {
  public:
    NTransform();
    NTransform(const NVector3& a_position, const NVector3& a_rotation, const NVector3& a_scale);

    NVector3 m_position;
    NVector3 m_rotation;
    NVector3 m_scale;

  private:
    NTransform(const NTransform&) = delete;
  };
}