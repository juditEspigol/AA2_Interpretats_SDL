#pragma once
#include "ImageRenderer.h"
#include <vector>

class AnimatedImageRenderer : public ImageRenderer
{
private:
	bool looping;

	std::vector<Vector2> deltas; 
	Vector2 initialSourceOffset; 
	int currentFrame;

	int fps;
	float frameTime; 
	float currentFrameTime;

public:
	AnimatedImageRenderer(Transform* transform, Vector2 sourceOffset, Vector2 sourceSize
		, const std::vector<Vector2>& deltas, bool looping, int fps, SDL_RendererFlip flipMode = SDL_FLIP_NONE)
		:ImageRenderer(transform, sourceOffset, sourceSize, flipMode)
		, deltas(deltas), looping(looping), currentFrame(0), fps(fps), currentFrameTime(0.0f), initialSourceOffset(sourceOffset)
	{
		frameTime = 1.0f / (float)fps; 
	}
	virtual void Update(float dt) override
	{
		currentFrameTime += dt; 

		if (currentFrameTime >= frameTime)
		{
			// UpdateTimer
			currentFrameTime -= frameTime * (floor)(currentFrameTime / frameTime); 

			// Check if I have to change frame
			if (looping)
				currentFrame = (currentFrame + 1) % deltas.size();
			else
				currentFrame = (currentFrame + 1) >= deltas.size() ? currentFrame : currentFrame + 1; 

			// Change frame
			sourceRect.x = initialSourceOffset.x + deltas[currentFrame].x;
			sourceRect.y = initialSourceOffset.y + deltas[currentFrame].y;
		}
	}

	virtual bool LastFrame() override
	{
		return (currentFrame + 1) >= deltas.size() ? true : false;
	}

	virtual void Reset() override
	{
		currentFrame = 0; 
		currentFrameTime = 0.0f; 
	}
};