#include "NGameObject.h"

namespace Nully
{
  NGameObject::NGameObject(ID3D11Device* a_device)
    : m_material("defaultMaterial", NShaderType::Default)
  {
    m_model.Load(a_device);
  }

  DirectX::XMMATRIX NGameObject::GetWorldMatrix() const
  {
    auto worldRot = DirectX::XMMatrixRotationX(m_transform.m_rotation.x) * DirectX::XMMatrixRotationY(m_transform.m_rotation.y) * DirectX::XMMatrixRotationZ(m_transform.m_rotation.z);
    auto worldScale = DirectX::XMMatrixScaling(m_transform.m_scale.x, m_transform.m_scale.y, m_transform.m_scale.z);
    auto worldPos = DirectX::XMMatrixTranslation(m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z);

    return DirectX::XMMatrixTranspose(worldRot * worldScale * worldPos);
  }
}
