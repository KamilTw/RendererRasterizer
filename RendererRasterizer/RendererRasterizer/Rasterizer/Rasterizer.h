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
	Buffer *buffer;

public:
	Rasterizer(Buffer *buffer);
	void draw(float3 v1, float3 v2, float3 v3, float4 c1, float4 c2, float4 c3);
	void draw(Model* model);
	void draw(Triangle* triangle);
	float xToCanonicalView(float x);
	float yToCanonicalView(float y);
};