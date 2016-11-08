#pragma once

#include <DirectXMath.h>

#include "NSingleton.h"
#include "NCameraMoveDirection.h"

namespace Nully
{

  class NCamera
  {
  public:
    NCamera(float speed);
    void Move(NCameraMoveDirection a_direction);
    DirectX::XMMATRIX& GetMVPMatrix();

    DirectX::XMMATRIX& GetViewMatrix();
    DirectX::XMMATRIX& GetProjectionMatrix();

    void Update();

  private:
    NCamera(const NCamera&); // no copy constructor

    DirectX::XMVECTOR m_position; // camera position
    DirectX::XMVECTOR m_focus; // camera look to
    DirectX::XMVECTOR m_up; // camera up vector
    DirectX::XMMATRIX m_vp; // view-projection matrix
    DirectX::XMMATRIX m_view;
    DirectX::XMMATRIX m_projection;

    float m_speed;

    const NScreenSize& m_screenSize;
  };
}
