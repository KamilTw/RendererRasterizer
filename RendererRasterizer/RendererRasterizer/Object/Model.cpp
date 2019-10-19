#include "Model.h"

void Model::addTriangle(Triangle *triangle)
{
	triangles.push_back(*triangle);
}

int Model::getTrianglesAmount()
{
	return triangles.size();
}

Triangle Model::getTriangle(int index)
{
	return triangles[index];
}