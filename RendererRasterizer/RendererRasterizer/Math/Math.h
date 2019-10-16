#pragma once
#include <algorithm>
#include <string>

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

struct Material
{
	float4 ka;
	float4 kd;
	float4 ks;
	std::string name;
};

inline float min(float x, float y, float z)
{
	return std::min(x, std::min(y, z));
}

inline float max(float x, float y, float z)
{
	return std::max(x, std::max(y, z));
}

inline float4 operator*(float4 color, float number)
{
	float r = color.r * number;
	float g = color.g * number;
	float b = color.b * number;

	return float4{ r, g, b, color.a };
}

inline float4 operator+(float4 c1, float4 c2)
{
	float r = c1.r + c2.r;
	float g = c1.g + c2.g;
	float b = c1.b + c2.b;

	return float4{ r, g, b, c1.a };
}