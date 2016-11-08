#include "NTransform.h"

namespace Nully
{
  NTransform::NTransform()
    : m_position(NVector3(0.0f, 0.0f, 0.0f)),
    m_rotation(NVector3(0.0f, 0.0f, 0.0f)),
    m_scale(NVector3(1.0f, 1.0f, 1.0f))
  {
  }

  NTransform::NTransform(const NVector3& a_position, const NVector3& a_rotation, const NVector3& a_scale)
    : m_position(a_position),
      m_rotation(a_rotation),
      m_scale(a_scale)
  {

  }
}

