﻿#include <iostream>
#include <ctime>
#include "Image/TgaBuffer.h"
#include "Object/Triangle.h"
#include "Rasterizer/Rasterizer.h"
#include "Object/ObjectLoader.h"
#include "Shaders/VertexProcessor.h"
#include "Lights/DirectionalLight.h"
#include "Lights/Light.h"

int main()
{
	std::clock_t start;
	double duration;
	start = std::clock();



	TgaBuffer *colorBuffer = new TgaBuffer(512, 512);
	Rasterizer rasterizer = Rasterizer(colorBuffer);

	VertexProcessor vp = VertexProcessor();
	vp.setPerspective(45, 1.0f, 0.1f, 100.0f);
	vp.setLookAt(float3{ 0, 0, 3 }, float3{ 0, 0, 0 }, float3{ 0, 1, 0 });
	rasterizer.setVp(vp);

	// Triangles
	vp.setIdentity();
	vp.multByScale(float3{ 2.4, 2.4, 2.4 });
	vp.multByRotation(10, float3{ 0, 1, 0 });
	vp.multByTranslation(float3{ -2.9f, -1.9f, -3 });

	Triangle t1 = Triangle(float3{ 1.0f, -1.0f, -2.0f }, float3{ 0.0f, 0.5f, -3.0f }, float3{ -1.0f, -1.0f, -5.0f },
								 float4{0, 0, 1, 1}, float4{ 1, 0, 0, 1 }, float4{ 0, 1, 0, 1 });
	Triangle t2 = Triangle(float3{ 1.0f, -0.5f, -2.0f }, float3{ -0.2f, 0.5f, -3.0f }, float3{ -0.5f, -0.5f, -5.0f },
								 float4{ 0, 1, 0, 1 }, float4{ 0, 1, 0, 1 }, float4{ 0, 1, 0, 1 });
	vp.lt(&t1);
	vp.lt(&t2);
	//rasterizer.draw(&t1);
	//rasterizer.draw(&t2);

	// Light
	Light* dl = new DirectionalLight();
	dl->setPosition(float3{ -0.5f, 0.0f, -0.5f });
	dl->setLightColor(float3{ 1.0f, 1.0f, 1.0f });
	dl->setAmbient(float3{ 0.2f, 0.2f, 0.2f });
	dl->setDiffuse(float3{ 0.6f, 0.6f, 0.6f });
	dl->setSpecular(float3{ 0.5f, 0.5f, 0.5f });
	dl->setShininess(10);
	rasterizer.addLight(dl);

	// Box
	ObjectLoader loader = ObjectLoader();
	Model box = loader.loadObject("sphere128");

	vp.setIdentity();
	vp.multByScale(float3{0.35, 0.35, 0.35 });
	vp.multByRotation(90, float3{ 0, 1, 0 });
	vp.multByTranslation(float3{ 0.0f, 0.0f, 0 });
	rasterizer.draw(&box, vp);

	vp.setIdentity();
	vp.multByScale(float3{ 0.35, 0.35, 0.35 });
	vp.multByRotation(90, float3{ 0, 1, 0 });
	vp.multByTranslation(float3{ 0.8f, 0.0f, 0 });
	rasterizer.draw(&box, vp);

	vp.setIdentity();
	vp.multByScale(float3{ 0.35, 0.35, 0.35 });
	vp.multByRotation(90, float3{ 0, 1, 0 });
	vp.multByTranslation(float3{ -0.8f, 0.0f, 0 });
	rasterizer.draw(&box, vp);

	vp.setIdentity();
	vp.multByScale(float3{ 0.35, 0.35, 0.35 });
	vp.multByRotation(90, float3{ 0, 1, 0 });
	vp.multByTranslation(float3{ 0.0f, 0.8f, 0 });
	rasterizer.draw(&box, vp);

	vp.setIdentity();
	vp.multByScale(float3{ 0.35, 0.35, 0.35 });
	vp.multByRotation(90, float3{ 0, 1, 0 });
	vp.multByTranslation(float3{ 0.0f, -0.8f, 0 });
	rasterizer.draw(&box, vp);



	colorBuffer->save("Image.tga");

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Rendered in " << duration << " seconds"<< std::endl;
}