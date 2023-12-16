#pragma once
#include "Vector2.h"

class AABB
{
private:
	Vector2 topLeft; 
	Vector2 size; 

public:
	AABB(Vector2 topLeft, Vector2 size)
		: topLeft(topLeft), size(size) {}

	bool CheckOverlappingAABB(AABB other); 
	bool CheckOverlappingPoint(Vector2 point); 

	inline Vector2 GetTopLeft() { return topLeft; }
	inline Vector2 GetSize() { return size; }
	inline void SetTopLeft(Vector2 _topLeft) { topLeft = _topLeft; }
	inline void SetSize(Vector2 _size) { size = _size; }
};

