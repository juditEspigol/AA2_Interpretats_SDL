#pragma once
#include <corecrt_math.h>

#define NORMALIZATION_THRESHOLD 0.0001f

class Vector2
{
public:
	float x; 
	float y; 

	Vector2()
		: x(0.0f), y(0.0f) {}

	Vector2(float _x, float _y)
		: x(_x), y(_y) {}

	void Normalize()
	{
		float lenght = Magnitude(); 
		if (lenght < NORMALIZATION_THRESHOLD)
		{
			x = 0.0f; 
			y = 0.0f;
		}
		else
		{
			x /= lenght;
			y /= lenght;
		}
	}
	float Magnitude()
	{
		return sqrt(x * x + y * y);
	}

	Vector2 operator+(Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(Vector2 other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator*(float product)
	{
		return Vector2(x * product, y * product);
	}
	Vector2 operator*(Vector2 other)
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 operator/(float product)
	{
		return Vector2(x / product, y / product);
	}
};

