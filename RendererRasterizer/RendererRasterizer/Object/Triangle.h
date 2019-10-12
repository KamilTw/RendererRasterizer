#pragma once
#include "../Math/Math.h"

class Triangle
{
public:
	float3 v1, v2, v3;
	float4 color;
public:
	Triangle(float3 v1, float3 v2, float3 v3, float4 color);
};