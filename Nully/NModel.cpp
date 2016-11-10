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
    //NObj objSpehre("sphere.obj");
    //NFaces faces = objSpehre.GetFaces();

    /*
    nuint32* indices = new nuint32[faces.size() * 6];

    nuint32 i = 0;
    for (auto face : faces)
    {
    indices[i] = face.v1;
    indices[i+1] = face.v2;
    indices[i+2] = face.v3;


    //indices[i+3] = face.v2;
    //indices[i+4] = face.v3;
    //indices[i+5] = face.v4;

    i += 6;
    }
    */

    nuint32 indices[] = 
    { 
      0, 1, 2, 3
    };


    //nuint32 indices[] = { 1, 2, 3, 0, 2, 3, 0 };
    m_indexBuffer.Create(a_device, indices, sizeof(indices) / sizeof(nuint32));//faces.size() * 6);
                                                                               //delete[] indices;




                                                                               /*
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

                                                                               */


    /*
    NVector3(1.000000, -1.000000, -1.000000),
    NVector3(1.000000, -1.000000, -1.000000),

    NVector3(1.000000, -1.000000, 1.000000),
    NVector3(1.000000, -1.000000, 1.000000),

    NVector3(-1.000000, -1.000000, 1.000000),
    NVector3(-1.000000, -1.000000, 1.000000),

    NVector3(-1.000000, -1.000000, -1.000000),
    NVector3(-1.000000, -1.000000, -1.000000),

    NVector3(1.000000, 1.000000, -0.999999),
    NVector3(1.000000, 1.000000, -0.999999),

    NVector3(0.999999, 1.000000, 1.000001),
    NVector3(0.999999, 1.000000, 1.000001),

    NVector3(-1.000000, 1.000000, 1.000000),
    NVector3(-1.000000, 1.000000, 1.000000),

    NVector3(-1.000000, 1.000000, -1.000000),
    NVector3(-1.000000, 1.000000, -1.000000)
    */

    NVertexDefault vertices[] =
    {
      NVector3(-1.000000, 1.000000, 0.000000),
      NVector3(0.000000, 1.000000, 0.000000),

      NVector3(1.000000, 1.000000, 0.000000),
      NVector3(0.000000, 1.000000, 0.000000),

      NVector3(1.000000, -1.000000, 0.000000),
      NVector3(1.000000, 0.000000, 0.000000),

      NVector3(-1.000000, -1.000000, 0.000000),
      NVector3(1.000000, 0.000000, 0.000000),
    /*
      NVector3(-0.5f, 0.0f, 0.0f),
      NVector3(0.0f, 0.0f, 1.0f),

      NVector3(0.5f, 0.0f, 0.0f),
      NVector3(0.0f, 1.0f, 0.0f),

      NVector3(0.0f, 1.0f, 0.0f),
      NVector3(0.0f, 1.0f, 0.0f),

      NVector3(1.0f, 1.0f, 0.0f),
      NVector3(0.0f, 1.0f, 0.0f),
      */
    };


    //m_vertexBuffer.Load(a_device, vertices, verts.size() * 2);
    m_vertexBuffer.Load(a_device, vertices, sizeof(vertices) / sizeof(NVertexDefault));

    //delete[] vertices;
  }
}
