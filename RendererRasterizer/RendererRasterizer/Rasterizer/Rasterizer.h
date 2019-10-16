#pragma once
#include <vector>
#include <iostream>
#include "../Image/Buffer.h"
#include "../Object/Triangle.h"
#include "..//Object/Model.h"

using namespace std;

class Rasterizer
{
private:
	vector<Triangle> t = vector<Triangle>();
	Buffer *buffer;

public:
	Rasterizer(Buffer *buffer);
	void draw(Triangle *t);
	void draw(Model* model);
	float xToCanonicalView(float x);
	float yToCanonicalView(float y);
};