#include "Buffer.h"

Buffer::Buffer(int w, int h)
{
	this->w = w;
	this->h = h;
	setSize(w * h);
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

void Buffer::setPixelColor(int x, int y, int r, int g, int b, int a)
{
	color[x + y * w] = a << 24 | r << 16 | g << 8 | b;
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
