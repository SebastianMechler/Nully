#pragma once

#include "NSingleton.h"
#include "NShader.h"
#include "NString.h"
#include "NShaderType.h"


namespace Nully
{
  class NMaterial
  {
  public:
    NMaterial();
    NMaterial(NString a_name, NShaderType a_type);

    void SetShader(NShaderType a_type);

    NString m_name;
    NShader* m_shader;
  };
}
