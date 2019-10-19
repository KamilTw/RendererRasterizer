#pragma once
#include <algorithm>
#include <string>

#define M_PI 3.14159265358979323846

union float3
{
	float data[3];
	struct
	{
		float x, y, z;
	};
};

struct float4
{
	float r, g, b, a;
};

struct float3x3
{
	float data[3][3];
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

inline float3 operator+(float3 v1, float3 v2)
{
	float x = v1.x + v2.x;
	float y = v1.y + v2.y;
	float z = v1.z + v2.z;

	return float3{ x, y, z };
}

inline float3 operator*(float3 v1, float3 v2)
{
	float x = v1.x * v2.x;
	float y = v1.y * v2.y;
	float z = v1.z * v2.z;

	return float3{ x, y, z };
}

inline float3 operator*(float3 vector, float3x3 matrix)
{
	float3 newVector;

	for (int i = 0; i < 3; i++)
	{
		float sum = 0;
		for (int j = 0; j < 3; j++)
		{
			sum += vector.data[j] * matrix.data[j][i];
		}
		newVector.data[i] = sum;
	}

	return newVector;
}