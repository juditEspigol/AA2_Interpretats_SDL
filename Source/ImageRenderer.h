#pragma once
#include "Renderer.h"

class ImageRenderer : public Renderer
{
public:
	ImageRenderer(Transform* transform, Vector2 sourceOffset, Vector2 sourceSize);
};