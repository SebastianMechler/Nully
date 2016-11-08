#pragma once

#include <D3D11.h>

#include "NVector3.h"
#include "NDirectxHelper.h"
#include "NIntern.h"

namespace Nully
{
  struct NVertexDefault
  {
    NVector3 position;
    NVector3 color;
  };

  class NVertexBuffer
  {
  public:
    NVertexBuffer();
    ~NVertexBuffer();

    bool Load(ID3D11Device* a_device, NVertexDefault* a_vertexData, nuint32 a_vertexCount);
    ID3D11Buffer* GetBuffer() const;
    nuint32 GetStride() const; // TODO: make this better...
    nuint32 GetVertexCount() const;

  private:
    ID3D11Buffer* m_vertexBuffer;
    nuint32 m_vertexCount;
    nuint32 m_stride;
  };
}