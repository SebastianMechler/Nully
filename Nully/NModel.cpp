#include "NModel.h"

namespace Nully
{
  NModel::NModel()
  {
    
  }

  NModel::~NModel()
  {
  }
  void NModel::Load(ID3D11Device* a_device)
  {
    nuint32 indices[] = {0, 1, 2, 4};
    m_indexBuffer.Create(a_device, indices, sizeof(indices) / sizeof(nuint32));

    NVertexDefault vertices[] =
    {
      NVector3(-0.5f, 0.0f, 0.0f),
      NVector3(0.0f, 0.0f, 1.0f),

      NVector3(0.5f, 0.0f, 0.0f),
      NVector3(0.0f, 1.0f, 0.0f),

      NVector3(0.0f, 1.0f, 0.0f),
      NVector3(0.0f, 1.0f, 0.0f),

      NVector3(1.0f, 1.0f, 0.0f),
      NVector3(0.0f, 1.0f, 0.0f),
    };

    m_vertexBuffer.Load(a_device, vertices, sizeof(vertices) / sizeof(NVertexDefault));
  }
}