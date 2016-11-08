#include "NShader.h"

namespace Nully
{
  NShader::NShader()
    : m_pixelShader(nullptr),
      m_vertexShader(nullptr),
      m_inputLayout(nullptr)
  {
  }
  void NShader::Release()
  {
    NSafeRelease(this->m_pixelShader);
    NSafeRelease(this->m_vertexShader);
    NSafeRelease(this->m_inputLayout);
  }
  bool NShader::HasLoadedSuccessfully()
  {
    return (m_pixelShader != nullptr && m_vertexShader != nullptr && m_inputLayout != nullptr);
  }
  NShader NShader::Load(ID3D11Device* a_device, const char * a_path)
  {
    NShader shader;

    if (a_path == nullptr || a_device == nullptr)
    {
      return shader;
    }

    // open file and read content into buffer
    NFile file;
    file.Open(a_path, NFileMode::Read);
    auto size = file.GetFileSize(a_path);
    char* buffer = new char[size];
    file.Read(buffer, size);

    ID3D10Blob* errorVS = nullptr;
    ID3D10Blob* errorPS = nullptr;
    ID3D10Blob* codeVS = nullptr;
    ID3D10Blob* codePS = nullptr;
    //
    // VertexShader (VS_Main)
    //
    if (NDirectXFailed(D3DCompile(buffer, size, a_path, nullptr, nullptr, "VS_Main", "vs_5_0", 0, 0, &codeVS, &errorVS)))
    {
      // file not found maybe.
    }
    else
    {
      a_device->CreateVertexShader(codeVS->GetBufferPointer(), codeVS->GetBufferSize(), nullptr, &shader.m_vertexShader);
    }

    if (errorVS != nullptr)
    {
      // error is set by D3DCompile function, print it out to console
      printf("%s", reinterpret_cast<char*>(errorVS->GetBufferPointer()));
    }

    //
    // PixelShader (PS_Main)
    //
    if (NDirectXFailed(D3DCompile(buffer, size, a_path, nullptr, nullptr, "PS_Main", "ps_5_0", 0, 0, &codePS, &errorPS)))
    {
      // file not found maybe.
    }
    else
    {
      a_device->CreatePixelShader(codePS->GetBufferPointer(), codePS->GetBufferSize(), nullptr, &shader.m_pixelShader);
    }

    if (errorPS != nullptr)
    {
      // error is set by D3DCompile function, print it out to console
      printf("%s", reinterpret_cast<char*>(errorPS->GetBufferPointer()));
    }

    if (NDirectXFailed(NShader::CreateInputLayoutFromVertexShader(codeVS, a_device, &shader.m_inputLayout)))
    {
      printf("%s %s", "Failed to create input-layout for shader: ", a_path);
    }

    // Cleanup memory
    NSafeRelease(errorPS);
    NSafeRelease(errorVS);
    NSafeRelease(codeVS);
    NSafeRelease(codePS);
    delete buffer;

    return shader;
  }
  HRESULT NShader::CreateInputLayoutFromVertexShader(ID3DBlob * a_shaderBytes, ID3D11Device * a_device, ID3D11InputLayout ** a_layout)
  {
    // Reflect shader info
    ID3D11ShaderReflection* pVertexShaderReflection = nullptr;
    if (NDirectXFailed(D3DReflect(a_shaderBytes->GetBufferPointer(), a_shaderBytes->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&pVertexShaderReflection))))
    {
      return S_FALSE;
    }

    // Get shader info
    D3D11_SHADER_DESC shaderDesc = {};
    pVertexShaderReflection->GetDesc(&shaderDesc);

    // Read input layout description from shader info
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
    for (nuint32 i = 0; i< shaderDesc.InputParameters; i++)
    {
      D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
      pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

      // fill out input element desc
      D3D11_INPUT_ELEMENT_DESC elementDesc;
      elementDesc.SemanticName = paramDesc.SemanticName;
      elementDesc.SemanticIndex = paramDesc.SemanticIndex;
      elementDesc.InputSlot = 0;
      elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
      elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
      elementDesc.InstanceDataStepRate = 0;

      // determine DXGI format
      if (paramDesc.Mask == 1)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
      else if (paramDesc.Mask <= 3)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
      else if (paramDesc.Mask <= 7)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
      else if (paramDesc.Mask <= 15)
      {
        if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
        else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }

      //save element desc
      inputLayoutDesc.push_back(elementDesc);
    }

    // Try to create Input Layout
    HRESULT hr = a_device->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), a_shaderBytes->GetBufferPointer(), a_shaderBytes->GetBufferSize(), a_layout);

    //Free allocation shader reflection memory
    pVertexShaderReflection->Release();
    return hr;
  }
}