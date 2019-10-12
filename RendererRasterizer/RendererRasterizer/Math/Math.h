#pragma once
#include <algorithm>

struct float3
{
	float x;
	float y;
	float z;
};

struct float4
{
	float r;
	float g;
	float b;
	float a;
};

inline float min(float x, float y, float z)
{
	return std::min(x, std::min(y, z));
}

inline float max(float x, float y, float z)
{
	return std::max(x, std::max(y, z));
}