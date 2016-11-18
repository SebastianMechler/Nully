#include "NModel.h"

namespace Nully
{
  NModel::NModel()
  {
    
  }

  NModel::~NModel()
  {
  }

  void NModel::Load(ID3D11Device* a_device)
  {
    nuint32 indices[] = 
    {
      // front

      
      0, 1, 2, 
      1, 2, 3

      //0, 1, 2, 3
      //1, 0, 2, 3,
      ////1, 2, 0, 3
      ////0, 1, 2, 3
      //6,4,5
      
      //// back
      //4,6,5,
      //4,7,6,
      //// left
      //4,5,1,
      //4,1,0,
      //// right
      //3,2,6,
      //3,6,7,
      ////top
      //1,5,6,
      //1,6,2,
      //// bottom
      //4,0,3,
      //4,3,7
    };


    m_indexBuffer.Create(a_device, indices, sizeof(indices) / sizeof(nuint32));
    

    
    NVertexDefault vertices[] =
    {
      NVector4(1.000000, -1.000000, -1.000000, 0),
      NVector4(1.000000, -1.000000, -1.000000, 0),

      NVector4(1.000000, -1.000000, 1.000000, 0),
      NVector4(1.000000, -1.000000, 1.000000, 0),

      NVector4(-1.000000, -1.000000, 1.000000, 0),
      NVector4(-1.000000, -1.000000, 1.000000, 0),

      NVector4(-1.000000, -1.000000, -1.000000, 0),
      NVector4(0.000000, 1.000000, 0.000000, 0),

      NVector4(1.000000, 1.000000, -0.999999, 0),
      NVector4(1.000000, 1.000000, -0.999999, 0),

      NVector4(0.999999, 1.000000, 1.000001, 0),
      NVector4(0.999999, 1.000000, 1.000001, 0),

      NVector4(-1.000000, 1.000000, 1.000000, 0),
      NVector4(-1.000000, 1.000000, 1.000000, 0),

      NVector4(-1.000000, 1.000000, -1.000000, 0),
      NVector4(-1.000000, 1.000000, -1.000000, 0),

      //NVector4(0, 1, 0, 0),
      //NVector4(1, 0, 0, 0),

      //NVector4(-1, 0, 0, 0),
      //NVector4(1, 0, 0, 0),

      //NVector4(1, 0, 0, 0),
      //NVector4(1, 0, 0, 0),

      //NVector4(0, -1, 0, 0),
      //NVector4(1, 0, 0, 0),
    };
    
    /*
    NVertexDefault vertices[] =
    {
      NVector4(-1.0f, 0.0f, 0.0f, 0.0f),
      NVector4(1.0f, 0.0f, 0.0f, 0.0f),

      NVector4(1.0f, 0.0f, 0.0f, 0.0f),
      NVector4(0.0f, 1.0f, 0.0f, 0.0f),

      NVector4(0.0f, -1.0f, 0.0f, 0.0f),
      NVector4(1.0f, 0.0f, 0.0f, 0.0f),

      //NVector4(0.5f, 1.0f, 0.0f, 0.0f),
      //NVector4(1.0f, 0.0f, 0.0f, 0.0f),

    };
    */

    m_vertexBuffer.Load(a_device, vertices, sizeof(vertices) / sizeof(NVertexDefault));
    

  }
}

/*
NObj objSpehre("cube.obj");
NFaces faces = objSpehre.GetFaces();

nuint32* indices = new nuint32[faces.size() * 4];

nuint32 i = 0;
for (auto face : faces)
{
indices[i] = face.v4;
indices[i + 1] = face.v3;
indices[i + 2] = face.v2;
indices[i + 3] = face.v1;

i += 4;
    }

    m_indexBuffer.Create(a_device, indices, faces.size() * 4);
    delete[] indices;

    NVertex verts = objSpehre.GetVertices();

    NVertexDefault* vertices = new NVertexDefault[verts.size() * 2];

    NVertexDefault tmp;

    i = 0;
    for (auto vertis : verts)
    {
      tmp.position = vertis;
      tmp.color = vertis;

      vertices[i] = tmp;

      i++;
    }


    m_vertexBuffer.Load(a_device, vertices, verts.size() * 2);

    delete[] vertices;
*/
