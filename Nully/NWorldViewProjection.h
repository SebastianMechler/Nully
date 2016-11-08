#pragma once

#include <DirectXMath.h>

namespace Nully
{
  struct NWorldViewProjection
  {
    DirectX::XMMATRIX world;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
  };
}

