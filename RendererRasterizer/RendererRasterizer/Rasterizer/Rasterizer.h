#pragma once
#include <vector>
#include <iostream>
#include "../Image/Buffer.h"
#include "../Object/Triangle.h"

using namespace std;

class Rasterizer
{
private:
	vector<Triangle> t = vector<Triangle>();
	Buffer *buffer;

public:
	Rasterizer(Buffer * buffer);
	void draw(Triangle t);
	float xToCanonicalView(float x);
	float yToCanonicalView(float y);
};