#pragma once
#include <Windows.h>

#include "NWindowAlignment.h"

namespace Nully
{
  struct NWindowDesc
  {
    LONG width;
    LONG height;
    const char* name;
    const char* className;
    bool isFullScreen;
    NWindowAlignment windowAlignment;
  };
}
