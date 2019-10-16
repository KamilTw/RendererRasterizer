#pragma once
#include <vector>
#include "../Math/Math.h"

using namespace std;

class Model
{
public:
	vector<float3> vertices;
	vector<float3> normals;
	vector<float> u;
	vector<float> v;
	vector<vector<int>> vertexFaces;
	vector<Material> materials;
	int numVertices;
	int numTriangles;
};
