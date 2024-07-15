#pragma once


struct VertexTexNormCoord
{
	struct
	{
		float x;
		float y;
		float z;
	} pos;

	struct
	{
		float u;
		float v;
	} tex;

	struct
	{
		float nx;
		float ny;
		float nz;
	} normal;
};