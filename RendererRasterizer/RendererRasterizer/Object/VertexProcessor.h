#pragma once
#include "..//Math/Math.h"
#include "Model.h"

class VertexProcessor
{
private:
	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;

public:
	float3 tr(float3 v);
	void lt(Model* model);
	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookAt(float3 eye, float3 center, float3 up);
	void setIdentity();
	void multByTranslation(float3 m);
	void multByScale(float3 v);
	void multByRotation(float a, float3 v);
};