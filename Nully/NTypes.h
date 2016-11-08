#pragma once

namespace Nully
{
  typedef unsigned __int8 nuint8;
  typedef unsigned __int16 nuint16;
  typedef unsigned __int32 nuint32;
  typedef unsigned __int64 nuint64;
  
  typedef __int8 nint8;
  typedef __int16 nint16;
  typedef __int32 nint32;
  typedef __int64 nint64;

  typedef unsigned char uchar;

  // architecture-specific
#ifdef _WIN64
  typedef nuint64 nsize_c;
#else
  typedef nuint32 nsize_c;
#endif
}
