#include "Model.h"

void Model::multiplyTrianglesByMatrix(float3x3 &matrix)
{
	for (int i = 0; i < getTrianglesAmount(); i++)
	{
		triangles[i].v1 = triangles[i].v1 * matrix;
		triangles[i].v2 = triangles[i].v2 * matrix;
		triangles[i].v3 = triangles[i].v3 * matrix;
	}
}

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

void Model::translate(float3 translateValues)
{
	for (int i = 0; i < getTrianglesAmount(); i++)
	{
		triangles[i].v1 = triangles[i].v1 + translateValues;
		triangles[i].v2 = triangles[i].v2 + translateValues;
		triangles[i].v3 = triangles[i].v3 + translateValues;
	}
}

void Model::scale(float3 scaleValues)
{
	for (int i = 0; i < getTrianglesAmount(); i++)
	{
		triangles[i].v1 = triangles[i].v1 * scaleValues;
		triangles[i].v2 = triangles[i].v2 * scaleValues;
		triangles[i].v3 = triangles[i].v3 * scaleValues;
	}
}

void Model::rotateXAxis(float degrees)
{
	float radians = (degrees * M_PI) / 180;

	float3x3 matrix = {{ {1,		    0,			   0},
						 {0, cos(radians), -sin(radians)},
						 {0, sin(radians),  cos(radians)}
					  }};

	multiplyTrianglesByMatrix(matrix);
}

void Model::rotateYAxis(float degrees)
{
	float radians = (degrees * M_PI) / 180;

	float3x3 matrix = {{ {cos(radians),  0, sin(radians)},
						 {0,			 1,			   0},
						 {-sin(radians), 0,  cos(radians)}
					  }};

	multiplyTrianglesByMatrix(matrix);
}

void Model::rotateZAxis(float degrees)
{
	float radians = (degrees * M_PI) / 180;

	float3x3 matrix = {{ {cos(radians), -sin(radians), 0},
						 {sin(radians),  cos(radians), 0},
						 {0,		 0,				   1}
					  }};

	multiplyTrianglesByMatrix(matrix);
}

void Model::rotate(float degrees, float3 v)
{
	float radians = (degrees * M_PI) / 180;
	float s = sin(radians);
	float c = cos(radians);

	float3x3 matrix = {{ {v.x*v.x*(1 - c) + c,		   v.x*v.y*(1 - c) - v.z*s,		v.x*v.z*(1 - c) + v.y*s},
						 {v.y*v.x*(1 - c) + v.z*s,	   v.y*v.y*(1 - c) + c,			v.y*v.z*(1 - c) - v.x*s},
						 {v.x*v.z*(1 - c) - v.y*s,	   v.y*v.z*(1 - c) + v.x*s,		v.z*v.z*(1 - c) + c}
					  }};

	multiplyTrianglesByMatrix(matrix);
}