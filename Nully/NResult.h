#pragma once

namespace Nully
{
  enum class NResult
  {
    Success,
    Nullptr,

    FileOpen,
    FileWrite,
    FileRead,
    FileReadLine,
  };
}