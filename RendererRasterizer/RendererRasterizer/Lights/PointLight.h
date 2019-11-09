#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
	float3 position;

public:
	float3 getPosition();
};