#include "NShaderManager.h"

namespace Nully
{
  NShaderManager::NShaderManager()
  {
  }
  bool NShaderManager::LoadShaderPool(ID3D11Device * a_device)
  {
    NShader defaultShader = NShader::Load(a_device, "default.hlsl");

    if (defaultShader.HasLoadedSuccessfully() == false)
    {
      return false;
    }

    m_map.insert(NShaderMapPair(NShaderType::Default, defaultShader));

    return true;
  }
  NShader * NShaderManager::GetShaderByType(NShaderType a_type)
  {
    return &m_map[a_type];
  }
  NShaderManager::~NShaderManager()
  {
    //std::for_each(m_map.begin(), m_map.end(), [](std::pair<NShaderType, NShader>& pair) {pair.second.Release(); });
    for (auto it = m_map.begin(); it != m_map.end(); it++)
    {
      it->second.Release();
    }
  }
}
