#include "NIndexBuffer.h"

namespace Nully
{
  NIndexBuffer::NIndexBuffer()
    : m_indexBuffer(nullptr)
  {
  }

  NIndexBuffer::~NIndexBuffer()
  {
    NSafeRelease(m_indexBuffer);
  }

  bool NIndexBuffer::Create(ID3D11Device* a_device, nuint32 * a_indices, const nuint32 a_indicesCount)
  {
    // Create indices.
    //nuint32 indices[] = { 0, 1, 2 };

    // Fill in a buffer description.
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(nuint32) * a_indicesCount;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    // Define the resource data.
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = a_indices;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    // Create the buffer with the device.
    if (NDirectXFailed(a_device->CreateBuffer(&bufferDesc, &InitData, &m_indexBuffer)))
    {
      return false;
    }

    return true;
  }

  ID3D11Buffer * NIndexBuffer::GetBuffer() const
  {
    return m_indexBuffer;
  }


}

