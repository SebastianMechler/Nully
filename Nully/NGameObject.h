#pragma once

#include <DirectXMath.h>

#include "NMaterial.h"
#include "NTransform.h"
#include "NModel.h"

namespace Nully
{
  class NGameObject
  {
  public:
    NGameObject(ID3D11Device* a_device);

    NMaterial m_material;
    NTransform m_transform;
    NModel m_model;

    DirectX::XMMATRIX GetWorldMatrix() const;

  private:

  };
}