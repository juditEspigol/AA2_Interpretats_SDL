#include "SmallRedPlane.h"

SmallRedPlane::SmallRedPlane(Pattern _pattern, float _waitingTime, Transform* _playerTransform)
	: EnemyPlane(1, 100, _playerTransform), timeToWait(_waitingTime)
{
	fireTime = 1.10f;
	lastFireTime = 0.0f;
	startLoop = 2.0f; 
	radiusLoop = 3; 
	pixelsPorSecond = Vector2(3, 0); 
	timeWaited = 0; 
	float posToSpawnY;

	BuildPattern(_pattern, posToSpawnY);

	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(16, 16);
	if (isRight)
	{
		transform->position = Vector2(-transform->size.x, posToSpawnY);
		transform->angle = -90.0f;
	}
	else
	{
		transform->position = Vector2(RENDERER.GetSizeWindow().x + transform->size.x, posToSpawnY);
		transform->angle = 90.0f;
	}
	transform->scale = Vector2(2.0f, 2.0f);
	transform->size = Vector2(16, 16);

	// RENDER
	renderers.emplace("Idle", new ImageRenderer(transform, Vector2(7, 283), Vector2(15, 15)));
	DeathAnimation();
	renderer = renderers["Idle"];

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void SmallRedPlane::Update(float dt)
{
	EnemyPlane::Update(dt);
	timeWaited += dt; 

	if (timeWaited <= timeToWait)
		return;

	if (isAlive)
		UpdateMovementPattern(dt);
	else
		DeathState();
}

void SmallRedPlane::UpdateMovementPattern(float dt)
{
	Vector2 direction = Vector2();

	movementTime += dt; 

	if (movementTime >= startLoop && movementTime <= (startLoop + 2.0f))
	{
		if (isRight)
			direction = Loop(dt, 1, -1);
		else
			direction = Loop(dt, -1, -1);
	}
	else
	{
		if(isRight)
			direction = Vector2(pixelsPorSecond.x, 0);
		else
			direction = Vector2(-pixelsPorSecond.x, 0);
	}
	transform->position = transform->position + direction;
}

Vector2 SmallRedPlane::Loop(float dt, int cosSigne, int sinSigne)
{
	Vector2 pos = Vector2();
	if (isUp)
	{
		pos = Vector2( cosSigne * cos(movementTime * M_PI) * radiusLoop, sinSigne * sin(movementTime * M_PI) * radiusLoop);
		SetRotation(GetRotation() - cosSigne * 180 * dt);
	}
	else
	{
		pos = Vector2(cosSigne * cos(movementTime * M_PI) * radiusLoop, -sinSigne * sin(movementTime * M_PI) * radiusLoop);
		SetRotation(GetRotation() + cosSigne * 180 * dt);
	}
	return pos;
}

void SmallRedPlane::DeathAnimation()
{
	std::vector<Vector2> deathDeltas{
		Vector2(0, 0),
		Vector2(20, 0),
		Vector2(20 * 2, 0),
		Vector2(20 * 3, 0),
		Vector2(20 * 4, 0),
		Vector2(20 * 5, 0)
	};
	renderers.emplace("Death", new AnimatedImageRenderer(transform, Vector2(157, 80), Vector2(20, 20), deathDeltas, false, 20));
}

void SmallRedPlane::BuildPattern(Pattern _pattern, float& posToSpawnY)
{
	switch (_pattern)
	{
	case A:
		isRight = true;
		isUp = false;
		posToSpawnY = 120;
		break;
	case B:
		isRight = false;
		isUp = true;
		posToSpawnY = 135;
		break;
	case C:
		isRight = false;
		isUp = false;
		posToSpawnY = 150;
		break;
	case D:
		isRight = true;
		isUp = true;
		posToSpawnY = 100;
		break;
	case E:
		isRight = true;
		isUp = false;
		posToSpawnY = 170;
		break;
	case F:
		isRight = false;
		isUp = false;
		posToSpawnY = 125;
	default:
		break;
	}
}
