#pragma once
#include "Vector2.h"
class Transform
{
public:
	Vector2 position;
	float angle;
	Vector2 scale;
	Vector2 size; // Conrtains width and height of the object
	bool centered; 

	Transform()
		: position(Vector2()), angle(0.0f), scale(Vector2(1.0f, 1.0f)), size(Vector2(1.0f, 1.0f)), 
		centered(true) {}
	Transform(Vector2 pos, float angle, Vector2 scale, Vector2 size, bool centered)
		: position(pos), angle(angle), scale(scale), size(size), centered(centered) {}
};

