#pragma once
#include "..//Math/Math.h"
#include "..//Shaders/VertexProcessor.h"

class Fragment;

class Light
{
private:
	float3 position;
	float3 lightColor;

	float3 ambient;
	float3 diffuse;
	float3 specular;
	float shininess;

	float constant;
	float linear;
	float quadratic;

public:
	virtual float3 calculate(float3& fragPosition, float3& fragNormal, VertexProcessor& vertexProcessor);

	float3 getPosition();
	float3 getLightColor();
	float3 getAmbient();
	float3 getDiffuse();
	float3 getSpecular();
	float getShininess();
	float getConstantAtten();
	float getLinearAtten();
	float getQuadraticAtten();

	void setPosition(float3 position);
	void setLightColor(float3 lightColor);
	void setAmbient(float3 ambient);
	void setDiffuse(float3 diffuse);
	void setSpecular(float3 specular);
	void setShininess(float shininess);
	void setAttenuation(float constant, float linear, float quadratic);
};