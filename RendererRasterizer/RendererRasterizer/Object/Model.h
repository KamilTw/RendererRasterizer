#pragma once
#include <vector>
#include "../Math/Math.h"
#include "..//Object/Triangle.h"

using namespace std;

class Model
{
private:
	vector<Triangle> triangles;

public:
	void addTriangle(Triangle* triangle);
	int getTrianglesAmount();
	Triangle getTriangle(int index);
};