#pragma once

#include "NVertexBuffer.h"
#include "NIndexBuffer.h"

namespace Nully
{
  class NModel
  {
  public:
    NModel();
    ~NModel();

    void Load(ID3D11Device* a_device);

    NVertexBuffer m_vertexBuffer;
    NIndexBuffer m_indexBuffer;
  };
}
