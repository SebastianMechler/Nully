#pragma once

#include <D3D11.h>
#include <map>

#include <algorithm>
#include "NShader.h"
#include "NShaderType.h"

namespace Nully
{
  typedef std::map<NShaderType, NShader> NShaderMap;
  typedef std::pair<NShaderType, NShader> NShaderMapPair;

  class NShaderManager
  {
  public:
    
    bool LoadShaderPool(ID3D11Device* a_device);
    NShader* GetShaderByType(NShaderType a_type);
    ~NShaderManager();

    friend class NSingleton;

  private:    
    NShaderManager();
    NShaderManager(const NShaderManager& other) = delete; // copy constructor

    NShaderMap m_map;
  };
}