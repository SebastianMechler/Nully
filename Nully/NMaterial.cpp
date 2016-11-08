#include "NMaterial.h"

namespace Nully
{
  NMaterial::NMaterial()
    : m_name(nullptr),
      m_shader(nullptr)
  {
    SetShader(NShaderType::Default);
  }

  NMaterial::NMaterial(NString a_name, NShaderType a_type)
    : m_shader(nullptr)
  {
    SetShader(a_type);
  }

  void NMaterial::SetShader(NShaderType a_type)
  {
    m_shader = NSingleton::GetShaderManager().GetShaderByType(a_type);
  }
}

