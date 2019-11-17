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

	float xToCanonicalView(float& x);
	float yToCanonicalView(float& y);

	float3 calculateColorPerVertex(float3& v, float4& c, float3& n);
	float4 interpolateColor(float3& c1Fragment, float3& c2Fragment, float3& c3Fragment, float& l1, float& l2, float& l3);
	float4 calculateColorPerPixel(float3& v1, float3& v2, float3& v3, float4& c1, float4& c2, float4& c3, float3& n1, float3& n2, float3& n3, float& l1, float& l2, float& l3);

	void maxToOne(float3& color);
	void addLight(Light* light);
	void setVp(VertexProcessor& vp);
};