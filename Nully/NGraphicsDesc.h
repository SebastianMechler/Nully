#pragma once

#include <windows.h>

#include "NIntern.h"

namespace Nully
{
  struct NGraphicsDesc
  {
    nuint32 width;
    nuint32 height;
    HWND hwnd;
  };
}