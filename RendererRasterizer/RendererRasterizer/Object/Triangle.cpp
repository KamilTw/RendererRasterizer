#include "Triangle.h"

Triangle::Triangle(float3 v1, float3 v2, float3 v3, float4 color)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->color = color;
}