#include "Nully.h"

using namespace Nully;

#include <vector>

enum class ObjType
{
  Vertex,
  VertexNormal,
  Name,
  Face,
  Uv,
  Unused,
};

ObjType GetObjType(char* buffer)
{
  char bufferTest[2];
  bufferTest[0] = *buffer;
  bufferTest[1] = *(buffer+1);

  if (bufferTest[0] == 'v' && bufferTest[1] == 'n')
  {
    return ObjType::VertexNormal;
  }
  if (bufferTest[0] == 'u' && bufferTest[1] == 'v')
  {
    return ObjType::Uv;
  }
  else if (bufferTest[0] == 'v')
  {
    return ObjType::Vertex;
  }
  else if (bufferTest[0] == 'f')
  {
    return ObjType::Face;
  }
  else if (bufferTest[0] == 'o')
  {
    return ObjType::Name;
  }
  else
  {
    return ObjType::Unused;
  }
}

NVector3 ToNVector3(char* buffer)
{
  NVector3 tmp;

  // remove \n
  *(buffer + strlen(buffer)-1) = '\0';

  auto len = strlen(buffer);
  std::vector<int> pos;

  // get positions of space ' '
  for (unsigned short i = 0; i < len; i++)
  {
    if (*(buffer + i) == ' ')
    {
      pos.push_back(i);
    }
  }

  // first two bytes are identifier, we dont need them anymore
  char* bufferT = buffer + pos[0] + 1;
  pos[1] -= (pos[0] + 1);
  pos[2] -= (pos[0] + 1);

  // create strings based on the bufferPostions of found spaces
  NString stringx = NString(bufferT, pos[1]);
  NString stringy = NString(bufferT + pos[1], pos[2] - pos[1]);
  NString stringz = NString(bufferT + pos[2], strlen(bufferT));
  
  // convert strings to floats
  tmp.x = std::stof(stringx, nullptr);
  tmp.y = std::stof(stringy, nullptr);
  tmp.z = std::stof(stringz, nullptr);

  return tmp;
}

NString ToName(char* buffer)
{
  // remove \n
  *(buffer + strlen(buffer) - 1) = '\0';

  return NString(buffer + 2);
}

struct NFace
{
  nuint32 v1;
  nuint32 v2;
  nuint32 v3;
  nuint32 v4;

  nuint32 normalIndex;
};

NFace ToFace(char* buffer)
{
  NFace face = {};

  // remove \n
  *(buffer + strlen(buffer) - 1) = '\0';

  auto len = strlen(buffer);
  std::vector<int> pos;

  // get positions of space ' '
  for (unsigned short i = 0; i < len; i++)
  {
    if (*(buffer + i) == ' ')
    {
      pos.push_back(i);
    }
  }

  // first two bytes are identifier, we dont need them anymore
  char* bufferT = buffer + pos[0] + 1;
  pos[1] -= (pos[0] + 1);
  pos[2] -= (pos[0] + 1);
  pos[3] -= (pos[0] + 1);

  // create strings based on the bufferPostions of found spaces
  NString f1 = NString(bufferT, pos[1]);
  NString f2 = NString(bufferT + pos[1], pos[2] - pos[1]);
  NString f3 = NString(bufferT + pos[2], pos[3] - pos[2]);
  NString f4 = NString(bufferT + pos[3], strlen(bufferT));

  auto x = f1.find_first_of('/');

  

  auto y = f1.find_last_of('/');
  NString last = f1.substr(y+1);

  return face;
}




void main()
{
  //NString cubeName;
  //std::vector<NVector3> vertices;
  //std::vector<NVector3> verticesNormal;
  //std::vector<NFace> faces;

  //NFile obj("cube.obj", NFileMode::Read);
  //char buffer[1024] = {};
  //ObjType type = ObjType::Unused;

  //while (obj.ReadLine(buffer, 1024) == NResult::FileReadLine)
  //{
  //  type = GetObjType(buffer);

  //  switch (type)
  //  {
  //  case ObjType::Vertex:
  //    vertices.push_back(ToNVector3(buffer));
  //    break;
  //  case ObjType::VertexNormal:
  //    verticesNormal.push_back(ToNVector3(buffer));
  //    break;
  //  case ObjType::Name:
  //    cubeName = ToName(buffer);
  //    break;
  //  case ObjType::Uv:
  //    break;
  //  case ObjType::Face:
  //    faces.push_back(ToFace(buffer));
  //    break;
  //  case ObjType::Unused:
  //    break;
  //  default:
  //    break;
  //  }
  //}


  NApplicationDesc applicationDesc = {};
  
  applicationDesc.windowDesc.width = 1024;
  applicationDesc.windowDesc.height = 768;
  applicationDesc.windowDesc.isFullScreen = false;
  applicationDesc.windowDesc.name = "Nully";
  applicationDesc.windowDesc.className = "NullyClass";
  applicationDesc.windowDesc.windowAlignment = NWindowAlignment::Center;

  applicationDesc.graphicsDesc.width = applicationDesc.windowDesc.width;
  applicationDesc.graphicsDesc.height = applicationDesc.windowDesc.height;
  applicationDesc.graphicsDesc.hwnd = 0;

  NApplication application;
  if (!application.Initialize(applicationDesc))
  {
    return; // failed to init app
  }

  application.Run();
}