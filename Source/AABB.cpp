#include "AABB.h"

bool AABB::CheckOverlappingAABB(AABB other)
{
	// X INTERSECTION
	float w1 = size.x;
	float w2 = other.size.x; 

	float dx;
	if (topLeft.x < other.topLeft.x)
	{
		dx = other.topLeft.x + other.size.x - topLeft.x; 
	}
	else
	{
		dx = topLeft.x + size.x - other.topLeft.x; 
	}
	bool intersectionX = dx < w1 + w2;

	// X INTERSECTION
	float h1 = size.y;
	float h2 = other.size.y;

	float dy;
	if (topLeft.y < other.topLeft.y)
	{
		dy = other.topLeft.y + other.size.y - topLeft.y;
	}
	else
	{
		dy = topLeft.y + size.y - other.topLeft.y;
	}
	bool intersectionY = dy < h1 + h2;

	return intersectionX && intersectionY; 
}

bool AABB::CheckOverlappingPoint(Vector2 point)
{
	bool insideX = point.x >= topLeft.x && point.x <= topLeft.x + size.x; 
	bool insideY = point.y >= topLeft.y && point.y <= topLeft.y + size.y; 

	return insideX && insideY; 
}
