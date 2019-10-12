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

	float dx32 = x3 - x2;
	float dx13 = x1 - x3;
	float dy13 = y1 - y3;

	float l1Denom = dy23 * dx13 + dx32 * dy13;
	float l2Denom = dy31 * dx23 + dx13 * dy23;

	bool tl1 = dy12 < 0 || (dy12 == 0 && dx12 > 0);
	bool tl2 = dy23 < 0 || (dy23 == 0 && dx23 > 0);
	bool tl3 = dy31 < 0 || (dy31 == 0 && dx31 > 0);

	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			if ((((dx12 * (y - y1) - dy12 * (x - x1) >= 0) && tl1) || (dx12 * (y - y1) - dy12 * (x - x1) > 0)) &&
				(((dx23 * (y - y2) - dy23 * (x - x2) >= 0) && tl2) || (dx23 * (y - y2) - dy23 * (x - x2) > 0)) &&
				(((dx31 * (y - y3) - dy31 * (x - x3) >= 0) && tl3) || (dx31 * (y - y3) - dy31 * (x - x3) > 0)))
			{
				// Color interpolation
				float l1 = (dy23 * (x - x3) + dx32 * (y - y3)) / l1Denom;
				float l2 = (dy31 * (x - x3) + dx13 * (y - y3)) / l2Denom;
				float l3 = 1 - l1 - l2;

				float4 interpolatedColor = t.c1 * l1 + t.c2 * l2 + t.c3 * l3;

				colorBuffer->setPixelColor(x, y, interpolatedColor);
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