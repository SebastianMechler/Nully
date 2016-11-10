#pragma once

#include <D3D11.h>

#include "NIntern.h"
#include "NDirectxHelper.h"

namespace Nully
{
  // TODO: % 16 in byteWidth, to have the best stride for performance...
  class NIndexBuffer
  {
  public:
    NIndexBuffer();
    ~NIndexBuffer();

    bool Create(ID3D11Device* a_device, nuint32* a_indices, const nuint32 a_indicesCount);
    ID3D11Buffer* GetBuffer() const;
    nuint32 GetCount() const;

  private:
    ID3D11Buffer* m_indexBuffer;
    nuint32 m_count;
  };
}