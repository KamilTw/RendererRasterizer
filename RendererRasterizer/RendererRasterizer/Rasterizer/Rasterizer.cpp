#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer * buffer)
{
	this->buffer = buffer;
	fragment = Fragment();
}

void Rasterizer::draw(float3& v11, float3& v22, float3& v33, float4& c1, float4& c2, float4& c3, float3& n11, float3& n22, float3& n33)
{
	// Vertex processor
	float3 v1 = vp.toProj(v11, 1);
	float3 v2 = vp.toProj(v22, 1);
	float3 v3 = vp.toProj(v33, 1);

	float3 n1 = vp.toProj(n11, 0);
	float3 n2 = vp.toProj(n22, 0);
	float3 n3 = vp.toProj(n33, 0);

	// From 0-1 to image resolution
	float x1 = xToCanonicalView(v1.x);
	float y1 = yToCanonicalView(v1.y);

	float x2 = xToCanonicalView(v2.x);
	float y2 = yToCanonicalView(v2.y);

	float x3 = xToCanonicalView(v3.x);
	float y3 = yToCanonicalView(v3.y);

	// Optimization
	float minX = min(x1, x2, x3);
	float maxX = max(x1, x2, x3);
	float minY = min(y1, y2, y3);
	float maxY = max(y1, y2, y3);

	// Culling
	minX = max(minX, 0.0f);
	maxX = min(maxX, float(buffer->getWidth() - 1));
	minY = max(minY, 0.0f);
	maxY = min(maxY, float(buffer->getHeight() - 1));

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
			// Left-handed system cause of 3ds max using it
			if ((((dx12 * (y - y1) - dy12 * (x - x1) <= 0) && tl1) || (dx12 * (y - y1) - dy12 * (x - x1) < 0)) &&
				(((dx23 * (y - y2) - dy23 * (x - x2) <= 0) && tl2) || (dx23 * (y - y2) - dy23 * (x - x2) < 0)) &&
				(((dx31 * (y - y3) - dy31 * (x - x3) <= 0) && tl3) || (dx31 * (y - y3) - dy31 * (x - x3) < 0)))
			{
				// Barycentric coordinates
				float l1 = (dy23 * (x - x3) + dx32 * (y - y3)) / l1Denom;
				float l2 = (dy31 * (x - x3) + dx13 * (y - y3)) / l2Denom;
				float l3 = 1 - l1 - l2;

				float depth = l1 * v1.z + l2 * v2.z + l3 * v3.z;

				if (depth < buffer->getDepth(x, y))
				{
					// Fragment shader
					float3 c1Fragment = float3{ c1.r, c1.g, c1.b } * fragment.calculate(v1, n1, vp);
					float3 c2Fragment = float3{ c2.r, c2.g, c2.b } * fragment.calculate(v2, n2, vp);
					float3 c3Fragment = float3{ c3.r, c3.g, c3.b } * fragment.calculate(v3, n3, vp);

					// Color interpolation
					float3 interpolatedColor = c1Fragment * l1 + c2Fragment * l2 + c3Fragment * l3;		
					maxToOne(interpolatedColor);

					float4 color = float4{ interpolatedColor.r, interpolatedColor.g, interpolatedColor.b, c1.a };
					
					buffer->setPixelColor(x, y, color);
					buffer->setDepth(x, y, depth);
				}
			}
		}	
	}
}

void Rasterizer::draw(Model* model, VertexProcessor& vp)
{
	setVp(vp);
	for (int i = 0; i < model->getIndexesAmount(); i++)
	{	
		draw(model->vertices[model->vIndexes[i].a], model->vertices[model->vIndexes[i].b], model->vertices[model->vIndexes[i].c],
			 model->materials[model->mIndexes[i]].kd, model->materials[model->mIndexes[i]].kd, model->materials[model->mIndexes[i]].kd,
			 model->normals[model->nIndexes[i].a], model->normals[model->nIndexes[i].b], model->normals[model->nIndexes[i].c]);
	}
}

void Rasterizer::draw(Triangle* triangle)
{
	for (int i = 0; i < 3; i++)
	{
		//draw(triangle->v[0], triangle->v[1], triangle->v[2],
			 //triangle->c[0], triangle->c[1], triangle->c[2]);
	}
}

float Rasterizer::xToCanonicalView(float x)
{
	return (x + 1) * buffer->getWidth() * 0.5f;
}

float Rasterizer::yToCanonicalView(float y)
{
	return (y + 1) * buffer->getHeight() * 0.5f;
}

void Rasterizer::maxToOne(float3 &color)
{
	float maxValue = max(color.r, max(color.g, color.b));

	if (maxValue > 1.0f)
	{
		color = color / maxValue;
	}
}

void Rasterizer::addLight(Light* light)
{
	fragment.addLight(light);
}

void Rasterizer::setVp(VertexProcessor vp)
{
	this->vp = vp;
}