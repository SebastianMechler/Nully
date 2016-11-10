#include "NDirectx.h"

namespace Nully
{
  NDirectx::NDirectx()
    : m_adapter(nullptr),
      m_swapchain(nullptr),
      m_device(nullptr),
      m_deviceContext(nullptr),
      m_renderTargetView(nullptr),
      m_textureDepthBuffer(nullptr),
      m_depthStencilState(nullptr),
      m_depthStencilView(nullptr),
      m_constantBuffer(nullptr),
      m_blendState(nullptr),
      m_camera(0.15f)
  {

  }

  NDirectx::~NDirectx()
  {
    NSafeRelease(m_adapter);
    NSafeRelease(m_swapchain);
    NSafeRelease(m_device);
    NSafeRelease(m_deviceContext);
    NSafeRelease(m_renderTargetView);
    NSafeRelease(m_textureDepthBuffer);
    NSafeRelease(m_depthStencilState);
    NSafeRelease(m_depthStencilView);
    NSafeRelease(m_constantBuffer);
    NSafeRelease(m_blendState);
  }
  bool NDirectx::Initialize(const NGraphicsDesc & a_graphicsDesc)
  {
    DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
    swapChainDesc.BufferDesc.Height = a_graphicsDesc.height;
    swapChainDesc.BufferDesc.Width = a_graphicsDesc.width;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;

    swapChainDesc.OutputWindow = a_graphicsDesc.hwnd; // HWND
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = 0;

    if (NDirectXFailed(D3D11CreateDeviceAndSwapChain(m_adapter, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr,
      0, D3D11_SDK_VERSION, &swapChainDesc, &m_swapchain, &m_device, nullptr, &m_deviceContext)))
    {
      return false;
    }

    ID3D11Texture2D* backBuffer = nullptr;
    if (NDirectXFailed(m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
    {
      return false;
    }

    if (NDirectXFailed(m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView)))
    {
      return false;
    }

    NSafeRelease(backBuffer);
    
    //
    // Depth-Buffer
    //
    // texture
    D3D11_TEXTURE2D_DESC textureDesc = { 0 };
    textureDesc.Width = a_graphicsDesc.width;
    textureDesc.Height = a_graphicsDesc.height;
    textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_D32_FLOAT;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.ArraySize = 1;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;

    if (NDirectXFailed(m_device->CreateTexture2D(&textureDesc, nullptr, &m_textureDepthBuffer)))
    {
      return false;
    }

    // depthStencilState
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
    //depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    if (NDirectXFailed(m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState)))
    {
      return false;
    }

    // depthStencilView
    if (NDirectXFailed(m_device->CreateDepthStencilView(m_textureDepthBuffer, nullptr, &m_depthStencilView)))
    {
      return false;
    }

    // set depthStencilState
    this->m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

    //D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
      //D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
    // Set topology
    m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // set viewport
    D3D11_VIEWPORT viewPort = { 0 };
    viewPort.Width = static_cast<FLOAT>(a_graphicsDesc.width);
    viewPort.Height = static_cast<FLOAT>(a_graphicsDesc.height);
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    m_deviceContext->RSSetViewports(1, &viewPort);

    // set render targets
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

    // Alpha Blending
    D3D11_BLEND_DESC blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());

    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    
    if (NDirectXFailed(m_device->CreateBlendState(&blendDesc, &m_blendState)))
    {
      return false;
    }


    m_deviceContext->OMSetBlendState(m_blendState, nullptr, 0xffffffff);


    // TODO: extract this to dynamic buffer
    CreateDynamicBuffer();

    return true;
  }
  void NDirectx::BeginDraw()
  {

  }
  void NDirectx::Draw()
  {
    // Sort all GameObjects
    static NGameObject go(m_device);
    go.m_material = NMaterial("myMaterial", NShaderType::Default);
    go.m_transform.m_position = NVector3(1.0f, 0.0f, 0.0f);
    go.m_transform.m_rotation = NVector3(0.0f, 0.0f, 0.0f);
    go.m_transform.m_scale = NVector3(1.0f, 1.0f, 1.0f);

    UpdateWorldViewProjectionMatrix(go);
        
    m_deviceContext->VSSetShader(go.m_material.m_shader->m_vertexShader, nullptr, 0);
    m_deviceContext->PSSetShader(go.m_material.m_shader->m_pixelShader, nullptr, 0);
    
    m_deviceContext->IASetInputLayout(go.m_material.m_shader->m_inputLayout);

    m_deviceContext->IASetIndexBuffer(go.m_model.m_indexBuffer.GetBuffer(), DXGI_FORMAT_R32_UINT, 0);

    ID3D11Buffer* buf = go.m_model.m_vertexBuffer.GetBuffer();

    UINT stride = go.m_model.m_vertexBuffer.GetStride();
    UINT offset = 0;
    m_deviceContext->IASetVertexBuffers(0, 1, &buf, &stride, &offset);

    //m_deviceContext->Draw(go.m_model.m_vertexBuffer.GetVertexCount(), 0);
    m_deviceContext->DrawIndexed(go.m_model.m_indexBuffer.GetCount(), 0, 0);

    go.m_transform.m_position = NVector3(0.0f, 0.0f, 0.0f);
    UpdateWorldViewProjectionMatrix(go);
    m_deviceContext->DrawIndexed(go.m_model.m_indexBuffer.GetCount(), 0, 0);

    go.m_transform.m_position = NVector3(0.0f, 2.5f, 0.0f);
    UpdateWorldViewProjectionMatrix(go);
    m_deviceContext->DrawIndexed(go.m_model.m_indexBuffer.GetCount(), 0, 0);

    go.m_transform.m_position = NVector3(3.0f, 2.5f, 0.0f);
    UpdateWorldViewProjectionMatrix(go);
    m_deviceContext->DrawIndexed(go.m_model.m_indexBuffer.GetCount(), 0, 0);

    go.m_transform.m_position = NVector3(2.0f, 2.5f, 2.0f);
    UpdateWorldViewProjectionMatrix(go);
    m_deviceContext->DrawIndexed(go.m_model.m_indexBuffer.GetCount(), 0, 0);
  }
  void NDirectx::EndDraw()
  {
    m_swapchain->Present(0, 0);
  }
  void * NDirectx::GetDevice()
  {
    return m_device;
  }
  void NDirectx::Clear()
  {
    m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

    float color[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
  }
  bool NDirectx::CreateDynamicBuffer()
  {
    NWorldViewProjection constBuffer = {};
    constBuffer.world = {};
    constBuffer.view = {};
    constBuffer.projection = {};    

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.ByteWidth = sizeof(NWorldViewProjection);
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;

    D3D11_SUBRESOURCE_DATA subData = {};
    subData.pSysMem = &bufferDesc;
    subData.SysMemPitch = 0;
    subData.SysMemSlicePitch = 0;
    
    if (NDirectXFailed(m_device->CreateBuffer(&bufferDesc, &subData, &m_constantBuffer)))
    {
      return false;
    }

    m_deviceContext->VSSetConstantBuffers(0, 1, &m_constantBuffer);

    return true;
  }
  void NDirectx::UpdateWorldViewProjectionMatrix(const NGameObject& a_gameObject)
  {
    // Update DynamicBuffer
    // map
    D3D11_MAPPED_SUBRESOURCE subresource = {};
    if (NDirectXFailed(m_deviceContext->Map(m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource)))
    {
      return;
    }

    // set new data
    NWorldViewProjection dynamicBuffer;
    dynamicBuffer.view = m_camera.GetViewMatrix();
    dynamicBuffer.projection = m_camera.GetProjectionMatrix();
    dynamicBuffer.world = a_gameObject.GetWorldMatrix();

    // setup world matrix
    if (GetAsyncKeyState(VK_UP))
    {
      m_camera.Move(NCameraMoveDirection::up);
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
      m_camera.Move(NCameraMoveDirection::down);
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
      m_camera.Move(NCameraMoveDirection::left);
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
      m_camera.Move(NCameraMoveDirection::right);
    }
    if (GetAsyncKeyState(VK_F1))
    {
      m_camera.Move(NCameraMoveDirection::forward);
    }
    if (GetAsyncKeyState(VK_F2))
    {
      m_camera.Move(NCameraMoveDirection::back);
    }


    *((NWorldViewProjection*)subresource.pData) = dynamicBuffer;

    // unmap
    m_deviceContext->Unmap(m_constantBuffer, 0);
  }
}
