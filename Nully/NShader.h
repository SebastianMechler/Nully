#pragma once

#include <D3D11.h>
#include <D3Dcompiler.h>
#include <vector>

#include "NDirectxHelper.h"
#include "NFile.h"
#include "NIntern.h"
#include "NDirectxHelper.h"

namespace Nully
{
  class NShader
  {
  public:
    NShader();
    void Release();
    bool HasLoadedSuccessfully();

    static NShader Load(ID3D11Device* a_device, const char* path);
    static HRESULT CreateInputLayoutFromVertexShader(ID3DBlob* a_shaderBytes, ID3D11Device* a_device, ID3D11InputLayout** a_layout);

    ID3D11InputLayout* m_inputLayout;
    ID3D11PixelShader* m_pixelShader;
    ID3D11VertexShader* m_vertexShader;
  };
}