#include "Triangle.h"

Triangle::Triangle(float3 v1, float3 v2, float3 v3, float4 c1, float4 c2, float4 c3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
}