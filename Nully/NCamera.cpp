#include "NCamera.h"

namespace Nully
{
  NCamera::NCamera(float speed)
    : m_speed(speed),
      m_screenSize(NSingleton::GetScreen().GetResolution())
  {
    // camera position
    m_position.m128_f32[0] = 0.0f;
    m_position.m128_f32[1] = 0.0f;
    m_position.m128_f32[2] = 10.0f;
    m_position.m128_f32[3] = 0.0f;

    // camera focus
    m_focus.m128_f32[0] = 0.1f;
    m_focus.m128_f32[1] = 0.0f;
    m_focus.m128_f32[2] = 0.0f;
    m_focus.m128_f32[3] = 0.0f;

    // camera up
    m_up.m128_f32[0] = 0.0f;
    m_up.m128_f32[1] = 1.0f;
    m_up.m128_f32[2] = 0.0f;
    m_up.m128_f32[3] = 0.0f;

    m_view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(m_position, m_focus, m_up));
    m_projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(3.1415f * 0.25f, (float)(m_screenSize.width / m_screenSize.height), 0.01f, 100.0f));

    Update();
  }
  void NCamera::Move(NCameraMoveDirection a_direction)
  {
    switch (a_direction)
    {
    case NCameraMoveDirection::up:
      m_position.m128_f32[1] += m_speed;
      m_focus.m128_f32[1] += m_speed;
      break;

    case NCameraMoveDirection::down:
      m_position.m128_f32[1] -= m_speed;
      m_focus.m128_f32[1] -= m_speed;
      break;

    case NCameraMoveDirection::left:
      m_position.m128_f32[0] += m_speed;
      m_focus.m128_f32[0] += m_speed;
      break;

    case NCameraMoveDirection::right:
      m_position.m128_f32[0] -= m_speed;
      m_focus.m128_f32[0] -= m_speed;
      break;

    case NCameraMoveDirection::back:
      m_position.m128_f32[2] += m_speed;
      m_focus.m128_f32[2] += m_speed;
      break;

    case NCameraMoveDirection::forward:
      m_position.m128_f32[2] -= m_speed;
      m_focus.m128_f32[2] -= m_speed;
      break;

    default:
      break;
    }

    Update();
  }

  DirectX::XMMATRIX& NCamera::GetMVPMatrix()
  {
    return m_vp;
  }

  DirectX::XMMATRIX& NCamera::GetViewMatrix()
  {
    return m_view;
  }

  DirectX::XMMATRIX& NCamera::GetProjectionMatrix()
  {
    return m_projection;
  }

  void NCamera::Update()
  {
    m_vp = DirectX::XMMatrixTranspose(
      DirectX::XMMatrixLookAtLH(m_position, m_focus, m_up)  // camera
      * DirectX::XMMatrixPerspectiveFovLH(3.1415f * 0.25f, m_screenSize.width / m_screenSize.height, 0.01f, 100.0f) // perspective
      );

    m_view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(m_position, m_focus, m_up));
    m_projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(3.1415f * 0.25f, m_screenSize.width / m_screenSize.height, 0.01f, 100.0f));
  }

}
