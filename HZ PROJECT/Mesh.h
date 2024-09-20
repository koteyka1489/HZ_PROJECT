#pragma once
#include "VertexTexNormCoord.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>




class Mesh
{
public:
	Mesh(std::string fileName);
	std::vector<VertexTexNormCoord>& GetVerTexNormCoord();
	std::vector<unsigned short>& GetIndices();

private:
	std::vector<VertexTexNormCoord> verTexNormCoord;
	std::vector<unsigned short> indices;
};