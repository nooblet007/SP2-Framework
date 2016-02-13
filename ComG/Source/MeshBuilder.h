#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlice);
	static Mesh* GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlice = 36);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStacks = 18, unsigned numSlice = 36);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlice);
	static Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif