#pragma once

class Buffer
{
protected:
	unsigned int *color;
	float depth;
	int w, h, minX, maxX, minY, maxY, length;

public:
	Buffer(int w, int h);
	void setSize(int size);
	void clearColor();
	void clearDepth();
	void setPixelColor(int x, int y, int r, int g, int b, int a);

	int getWidth();
	int getHeight();
	int getLength();
};