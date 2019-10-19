#pragma once
#include <vector>
#include "../Math/Math.h"
#include "..//Object/Triangle.h"

using namespace std;

class Model
{
private:
	vector<Triangle> triangles;

	void multiplyTrianglesByMatrix(float3x3 &matrix);

public:
	void addTriangle(Triangle* triangle);
	int getTrianglesAmount();
	Triangle getTriangle(int index);

	void translate(float3 translateValues);
	void scale(float3 scaleValues);
	void rotateXAxis(float degrees);
	void rotateYAxis(float degrees);
	void rotateZAxis(float degrees);
	void rotate(float degrees, float3 v);
};