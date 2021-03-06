#pragma once

#include "NGraphicsDesc.h"
#include "NFillMode.h"

namespace Nully
{
  class IGraphics
  {
  public:
    virtual bool Initialize(const NGraphicsDesc& a_graphicsDesc) = 0;
    virtual void BeginDraw() = 0;
    virtual void Draw() = 0;
    virtual void EndDraw() = 0;
    virtual void* GetDevice() = 0;
    virtual void Clear() = 0;
    virtual void SetFillMode(const NFillMode& a_fillMode) = 0;

    virtual ~IGraphics() {};
  };
}