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
    NObj objSpehre("sphere.obj");
    NFaces faces = objSpehre.GetFaces();

    nuint32* indices = new nuint32[faces.size() * 4];

    nuint32 i = 0;
    for (auto face : faces)
    {
      indices[i] = face.v1--;
      indices[i + 1] = face.v2--;
      indices[i + 2] = face.v3--;
      indices[i + 3] = face.v4--;

      //indices[i+3] = face.v2;
      //indices[i+4] = face.v3;
      //indices[i+5] = face.v4;

      i += 4;
    }

    //nuint32 indices[] = {0, 1, 2, 4};
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



    /*
    NVertexDefault vertices[] =
    {
    NVector3(-0.5f, 0.0f, 0.0f),
    NVector3(0.0f, 0.0f, 1.0f),

    NVector3(0.5f, 0.0f, 0.0f),
    NVector3(0.0f, 1.0f, 0.0f),

    NVector3(0.0f, 1.0f, 0.0f),
    NVector3(0.0f, 1.0f, 0.0f),

    NVector3(1.0f, 1.0f, 0.0f),
    NVector3(0.0f, 1.0f, 0.0f),
    };
    */

    m_vertexBuffer.Load(a_device, vertices, verts.size() * 2);

    delete[] vertices;
  }
}
