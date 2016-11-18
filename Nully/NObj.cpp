#include "NObj.h"

namespace Nully
{
  NObj::NObj()
  {
  }

  NObj::NObj(const char * a_file)
  {
    Load(a_file);
  }

  void NObj::Load(const char * a_file)
  {
    if (a_file == nullptr)
    {
      return;
    }
    
    // Open File and Read the Size
    NFile obj;
    obj.Open(a_file, NFileMode::Read);
    auto size = obj.GetFileSize(a_file);
    
    // wrong size? return
    if (size == 0)
    {
      return;
    }

    // create unique_ptr so the delete[] will be called on leaving scope
    std::unique_ptr<char[]> buffer(new char[size + 1]);
    
    // buffer which will be incremented and worked with
    char* workBuffer = buffer.get();

    // read the whole file into buffer
    obj.Read(workBuffer, size);
    *(workBuffer + size) = '\0'; // set zero termination

    bool isWorkDone = false;
    nuint32 lineLength = 0;
    NObjDataType type = NObjDataType::Unused;

    
    while (isWorkDone == false)
    {
      type = GetObjType(workBuffer); // get object type from the first two characters

      lineLength = GetNewLineLength(workBuffer, isWorkDone); // find the length of the line which is determined by '\n' character
      switch (type)
      {
      case NObjDataType::Vertex:
      case NObjDataType::Normal:
        ToNVector4(workBuffer, type, lineLength);
        break;
      case NObjDataType::Name:
        ToName(workBuffer, lineLength);
        break;
      case NObjDataType::Uv:
        break;
      case NObjDataType::Face:
        ToFace(workBuffer, lineLength);
        break;
      case NObjDataType::Unused:
        break;
      default:
        break;
      }

      // increment the buffer which will then point to the next line
      workBuffer += lineLength;
    }
    
  }
  NVertex& NObj::GetVertices()
  {
    return m_vertices;
  }
  NVertex& NObj::GetNormals()
  {
    return m_normals;
  }
  NFaces& NObj::GetFaces()
  {
    return m_faces;
  }
  NString& NObj::GetName()
  {
    return m_objName;
  }
  NObjDataType NObj::GetObjType(char * a_buffer)
  {
    if (a_buffer == nullptr)
    {
      return NObjDataType::Unused;
    }

    char objType[2];
    objType[0] = *a_buffer;
    objType[1] = *(a_buffer + 1);

    if (objType[0] == 'v' && objType[1] == 'n')
    {
      return NObjDataType::Normal;
    }
    if (objType[0] == 'v' && objType[1] == 't')
    {
      return NObjDataType::Uv;
    }
    else if (objType[0] == 'v')
    {
      return NObjDataType::Vertex;
    }
    else if (objType[0] == 'f')
    {
      return NObjDataType::Face;
    }
    else if (objType[0] == 'o')
    {
      return NObjDataType::Name;
    }
    else
    {
      return NObjDataType::Unused;
    }
  }
  void NObj::ToNVector4(char* a_buffer, NObjDataType a_type, nuint32 a_lineLength)
  {
    NVector4 tmp;

    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength -1) = ' '; // -1 to come to the '\n'

    char tmpX;
    if (a_type == NObjDataType::Vertex)
    {
      // this is a vertex
      // v 0.137950 0.980785 -0.137950
      //sscanf(buffer, "%c %f %f %f", &tmpX, &tmp.x, &tmp.y, &tmp.z);
      sscanf_s(a_buffer, "%c %f %f %f", &tmpX, 1, &tmp.x, &tmp.y, &tmp.z);
      m_vertices.push_back(tmp);
    }
    else if (a_type == NObjDataType::Normal)
    {
      // this is a vertex normal
      // vn 0.0464 0.8810 -0.4709
      //sscanf(buffer, "%c%c %f %f %f", &tmpX, &tmpX, &tmp.x, &tmp.y, &tmp.z);
      sscanf_s(a_buffer, "%c%c %f %f %f", &tmpX, 1, &tmpX, 1, &tmp.x, &tmp.y, &tmp.z);
      m_normals.push_back(tmp);
    }
  }

  void NObj::ToName(char* a_buffer, nuint32 a_lineLength)
  {
    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

    // incoming buffer looks like:
    // o Cube
    // so we have to move by two bytes
    m_objName = NString(a_buffer+2, a_lineLength-2);
  }
  void NObj::ToFace(char * a_buffer, nuint32 a_lineLength)
  {
    NFace face = {};

    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

    char tmp;
    sscanf_s(a_buffer, "%c %u//%u %u//%u %u//%u %u//%u", &tmp, 1, &face.v1, &face.normalIndex, &face.v2, &face.normalIndex, &face.v3, &face.normalIndex, &face.v4, &face.normalIndex);

    m_faces.push_back(face);
  }
  nuint32 NObj::GetNewLineLength(const char* buffer, bool& a_isNullterminationFound)
  {
    //nuint32 len = strlen(buffer) + 1; // +1 cause of \0

    for (nuint32 i = 0; i < 1024; i++)
    {
      if (*buffer == '\n')
      {
        // found new line
        return i+1;
      }
      else if (*buffer == '\0')
      {
        // end is found
        a_isNullterminationFound = true;
        return i+1;
      }

      buffer++;
    }
        
    a_isNullterminationFound = true;
    return 0;
  }
}

