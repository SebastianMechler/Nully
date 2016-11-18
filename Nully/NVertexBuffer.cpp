#include "NVertexBuffer.h"

namespace Nully
{
  NVertexBuffer::NVertexBuffer()
    : m_vertexBuffer(nullptr),
      m_stride(0),
      m_vertexCount(0)
  {
  }
  NVertexBuffer::~NVertexBuffer()
  {
    NSafeRelease(m_vertexBuffer);
  }
  bool NVertexBuffer::Load(ID3D11Device* a_device, NVertexDefault* a_vertexData, nuint32 a_vertexCount)
  {
    if (a_vertexData == nullptr)
    {
      return false;
    }

    m_vertexCount = a_vertexCount;
    m_stride = sizeof(NVertexDefault);

    // Fill in a buffer description.
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = (m_stride * m_vertexCount + 15) / 16 * 16;;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    // Fill in the subresource data.
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = a_vertexData;
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    // Create the vertex buffer.
    if (NDirectXFailed(a_device->CreateBuffer(&bufferDesc, &InitData, &m_vertexBuffer)))
    {
      return false;
    }

    return true;
  }
  ID3D11Buffer * NVertexBuffer::GetBuffer() const
  {
    return m_vertexBuffer;
  }
  nuint32 NVertexBuffer::GetStride() const
  {
    return m_stride;
  }
  nuint32 NVertexBuffer::GetVertexCount() const
  {
    return m_vertexCount;
  }
}
