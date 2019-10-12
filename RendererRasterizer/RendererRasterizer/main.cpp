#include <iostream>
#include <ctime>
#include "Image/TgaBuffer.h"
#include "Object/Triangle.h"
#include "Rasterizer/Rasterizer.h"

int main()
{
	std::clock_t start;
	double duration;
	start = std::clock();



	TgaBuffer *colorBuffer = new TgaBuffer(256, 256);
	Triangle triangle = Triangle(float3{ -0.5f, -0.0f, -1.0f }, float3{ 0.0f, 0.5f, 0.0f }, float3{ 0.9f, -0.0f, 0.0f },
								 float4{1, 1, 1, 1});

	Rasterizer rasterizer = Rasterizer(colorBuffer);
	rasterizer.draw(triangle);
	colorBuffer->save("Image.tga");



	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Rendered in " << duration << " seconds"<< std::endl;
}