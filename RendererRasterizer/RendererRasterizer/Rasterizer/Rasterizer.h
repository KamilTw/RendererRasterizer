#pragma once
#include <vector>
#include <iostream>
#include "../Image/Buffer.h"
#include "../Object/Triangle.h"
#include "..//Object/Model.h"
#include "..//Shaders/VertexProcessor.h"
#include "..//Shaders/Fragment.h"
#include "..//Lights/Light.h"

using namespace std;

class Rasterizer
{
private:
	Buffer *buffer;
	Fragment fragment;
	VertexProcessor vp;

public:
	Rasterizer(Buffer *buffer);
	void draw(float3& v1, float3& v2, float3& v3, float4& c1, float4& c2, float4& c3, float3& n1, float3& n2, float3& n3);
	void draw(Model* model, VertexProcessor& vp);
	void draw(Triangle* triangle);
	float xToCanonicalView(float x);
	float yToCanonicalView(float y);
	void maxToOne(float3& color);
	void addLight(Light* light);
	void setVp(VertexProcessor vp);
};