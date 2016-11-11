#pragma once

#include <D3D11.h>
#include <DirectXMath.h>

#include "IGraphics.h"
#include "NDirectxHelper.h"
#include "NGameObject.h"
#include "NCamera.h"
#include "NWorldViewProjection.h"

namespace Nully
{
  class NDirectx : public IGraphics
  {
  public:
    NDirectx();
    ~NDirectx();
    bool Initialize(const NGraphicsDesc& a_graphicsDesc) override;
    void BeginDraw() override;
    void Draw() override;
    void EndDraw() override;
    void* GetDevice() override;
    void Clear() override;
    void SetFillMode(const NFillMode& a_fillMode) override;

    bool CreateDynamicBuffer();
    void UpdateWorldViewProjectionMatrix(const NGameObject& a_gameObject);
    
    
  private:
    IDXGIAdapter* m_adapter;
    IDXGISwapChain* m_swapchain;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    ID3D11RenderTargetView* m_renderTargetView;

    ID3D11Texture2D* m_textureDepthBuffer;
    ID3D11DepthStencilState* m_depthStencilState;
    ID3D11DepthStencilView* m_depthStencilView;

    ID3D11Buffer* m_constantBuffer;
    ID3D11BlendState* m_blendState;
    ID3D11RasterizerState* m_rasterizerState;

    NCamera m_camera;
  };
}












