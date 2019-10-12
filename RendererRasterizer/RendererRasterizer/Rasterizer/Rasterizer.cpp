#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer *colorBuffer)
{
	this->colorBuffer = colorBuffer;
}

void Rasterizer::draw(Triangle t)
{
	// From 0-1 to image resolution
	float x1 = xToCanonicalView(t.v1.x);
	float y1 = yToCanonicalView(t.v1.y);

	float x2 = xToCanonicalView(t.v2.x);
	float y2 = yToCanonicalView(t.v2.y);

	float x3 = xToCanonicalView(t.v3.x);
	float y3 = yToCanonicalView(t.v3.y);

	// Optimization
	float minX = min(x1, x2, x3);
	float maxX = max(x1, x2, x3);
	float minY = min(y1, y2, y3);
	float maxY = max(y1, y2, y3);

	// Culling
	minX = max(minX, 0.0f);
	maxX = min(maxX, float(colorBuffer->getWidth() - 1));
	minY = max(minY, 0.0f);
	maxY = min(maxY, float(colorBuffer->getHeight() - 1));

	float dx12 = x1 - x2;
	float dx23 = x2 - x3;
	float dx31 = x3 - x1;
	float dy12 = y1 - y2;
	float dy23 = y2 - y3;
	float dy31 = y3 - y1;

	for (int y = minY; y < maxY; y++)
	{
		for (int x = minX; x < maxX; x++)
		{
			if (dx12 * (y - y1) - dy12 * (x - x1) > 0 &&
				dx23 * (y - y2) - dy23 * (x - x2) > 0 &&
				dx31 * (y - y3) - dy31 * (x - x3) > 0)
			{
				colorBuffer->setPixelColor(x, y, t.color);
			}
		}
	}
}

float Rasterizer::xToCanonicalView(float x)
{
	return (x + 1) * colorBuffer->getWidth() * 0.5f;
}

float Rasterizer::yToCanonicalView(float y)
{
	return (y + 1) * colorBuffer->getHeight() * 0.5f;
}