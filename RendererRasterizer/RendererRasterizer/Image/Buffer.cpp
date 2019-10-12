#include "Buffer.h"

Buffer::Buffer(int w, int h)
{
	this->w = w;
	this->h = h;

	setSize(w * h);
	depth = new float[w * h];

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			setPixelColor(x, y, float4{ 0, 0, 0, 1 });
			setDepth(x, y, 1000000);
		}
	}
}

void Buffer::setSize(int size)
{
	color = new unsigned int[size];
}

void Buffer::clearColor()
{
	color = new unsigned int[w * h];
}

void Buffer::clearDepth()
{
	depth = 0;
}

void Buffer::setPixelColor(int x, int y, float4 rgba)
{
	color[x + y * w] = (int)(rgba.a * 255) << 24 |
					   (int)(rgba.r * 255) << 16 |
					   (int)(rgba.g * 255) << 8 |
					   (int)(rgba.b * 255);
	//color[x + y * w] = 16777216 * a + 65536 * r + 256 * g + b;
}

int Buffer::getWidth()
{
	return w;
}

int Buffer::getHeight()
{
	return h;
}

int Buffer::getLength()
{
	return w * h;
}

float Buffer::getDepth(int x, int y)
{
	return depth[x + y * w];
}

void Buffer::setDepth(int x, int y, float newDepth)
{
	depth[x + y * w] = newDepth;
}