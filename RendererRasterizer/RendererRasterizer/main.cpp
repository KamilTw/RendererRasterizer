#include <iostream>
#include <ctime>
#include "Image/TgaBuffer.h"
#include "Object/Triangle.h"
#include "Rasterizer/Rasterizer.h"
#include "Object/ObjectLoader.h"

int main()
{
	std::clock_t start;
	double duration;
	start = std::clock();



	TgaBuffer *colorBuffer = new TgaBuffer(512, 512);
	Triangle t1 = Triangle(float3{ 1.0f, -1.0f, 0.0f }, float3{ 0.0f, 0.5f, 0.0f }, float3{ -1.0f, -1.0f, 0.0f },
								 float4{0, 0, 1, 1}, float4{ 1, 0, 0, 1 }, float4{ 0, 1, 0, 1 });
	Triangle t2 = Triangle(float3{ 1.0f, -0.5f, -5.0f }, float3{ -0.2f, 0.5f, 5.0f }, float3{ -0.5f, -0.5f, -5.0f },
								 float4{ 0, 1, 0, 1 }, float4{ 0, 1, 0, 1 }, float4{ 0, 1, 0, 1 });


	Rasterizer rasterizer = Rasterizer(colorBuffer);
	//rasterizer.draw(&t1);
	//rasterizer.draw(&t2);
	

	ObjectLoader loader = ObjectLoader();
	Model box = loader.loadObject("box");
	rasterizer.draw(&box);


	colorBuffer->save("Image.tga");

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Rendered in " << duration << " seconds"<< std::endl;
}