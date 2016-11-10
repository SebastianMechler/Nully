#pragma once

#include <iostream>
#include <vector>
#include <memory> // shared_ptr

#include "NObjFace.h"
#include "NObjDataType.h"
#include "NVector3.h"
#include "NString.h"
#include "NFile.h"

namespace Nully
{
  typedef std::vector<NVector3> NVertex;
  typedef std::vector<NFace> NFaces;
  
  class NObj
  {
  public:
    NObj();
    NObj(const char* a_file);
    void Load(const char* a_file);

    NVertex& GetVertices();
    NVertex& GetNormals();
    NFaces& GetFaces();
    NString& GetName();

  private:
    NObjDataType GetObjType(char* buffer);
    void ToNVector3(char* a_buffer, NObjDataType a_type, nuint32 a_lineLength);
    void ToName(char* a_buffer, nuint32 a_lineLength);
    void ToFace(char* a_buffer, nuint32 a_lineLength);

    nuint32 GetNewLineLength(const char* buffer, bool& a_isNullterminationFound);

    NString m_objName;
    NVertex m_vertices;
    NVertex m_normals;
    NFaces m_faces;
  };
}
