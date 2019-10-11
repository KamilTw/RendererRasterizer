#include <iostream>
#include "TgaBuffer.h"

int main()
{
	TgaBuffer colorBuffer = TgaBuffer(256, 256);

	for (int y = 0; y < colorBuffer.getHeight(); y++)
	{
		for (int x = 0; x < colorBuffer.getWidth(); x++)
		{
			colorBuffer.setPixelColor(x, y, 255, 0, 0, 255);
		}
	}

	colorBuffer.save("Image.tga");
}