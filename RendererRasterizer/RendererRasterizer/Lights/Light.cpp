#include "Light.h"

float3 Light::calculate(float3& fragPosition, float3& fragNormal, VertexProcessor& vertexProcessor)
{
	return float3{ 0, 0, 0 };
}

float3 Light::getPosition()
{
	return position;
}

float3 Light::getLightColor()
{
	return lightColor;
}

float3 Light::getAmbient()
{
	return ambient;
}

float3 Light::getDiffuse()
{
	return diffuse;
}

float3 Light::getSpecular()
{
	return specular;
}

float Light::getShininess()
{
	return shininess;
}

float Light::getConstantAtten()
{
	return constant;
}

float Light::getLinearAtten()
{
	return linear;
}

float Light::getQuadraticAtten()
{
	return quadratic;
}

void Light::setPosition(float3 position)
{
	this->position = position;
}

void Light::setLightColor(float3 lightColor)
{
	this->lightColor = lightColor;
}

void Light::setAmbient(float3 ambient)
{
	this->ambient = ambient;
}

void Light::setDiffuse(float3 diffuse)
{
	this->diffuse = diffuse;
}

void Light::setSpecular(float3 specular)
{
	this->specular = specular;
}

void Light::setShininess(float shininess)
{
	this->shininess = shininess;
}

void Light::setAttenuation(float constant, float linear, float quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}