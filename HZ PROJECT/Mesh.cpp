#include "Mesh.h"

Mesh::Mesh(std::string fileName)
{
	Assimp::Importer imp;
	const auto pModel = imp.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	const auto pMesh = pModel->mMeshes[0];
	
    for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
    {
        VertexTexNormCoord vertex;

        vertex.pos.x = pMesh->mVertices[i].x;
        vertex.pos.y = pMesh->mVertices[i].y;
        vertex.pos.z = pMesh->mVertices[i].z;

        if (pMesh->HasNormals())
        {
            vertex.normal.nx = pMesh->mNormals[i].x;
            vertex.normal.ny = pMesh->mNormals[i].y;
            vertex.normal.nz = pMesh->mNormals[i].z;
        }

        if (pMesh->mTextureCoords[0])
        {
            vertex.tex.u = pMesh->mTextureCoords[0][i].x;
            vertex.tex.v = pMesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertex.tex.u = 0.0f;
            vertex.tex.v = 0.0f;
        }

        verTexNormCoord.push_back(vertex);
    }

    for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
    {
        aiFace face = pMesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

}

std::vector<VertexTexNormCoord>& Mesh::GetVerTexNormCoord()
{
	return verTexNormCoord;
}

std::vector<unsigned short>& Mesh::GetIndices()
{
	return indices;
}
