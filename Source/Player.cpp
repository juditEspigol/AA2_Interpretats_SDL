#include "Player.h"

Player::Player()
{
	isPendingDestroy = false;
	// PLAYER SETTINGS 
	isRolling = false;
	force = 40; 
	fireTime = 1.00f;
	lastFireTime = 1.10f;
	doubleFire = false;

	// TRANSFORM
	transform.position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.75);
	transform.angle = 0.0f;
	transform.scale = Vector2(2.0f, 2.0f);
	transform.size = Vector2(16, 16);

	// RENDER
	//renderer = new ImageRenderer(&transform, Vector2(5, 6), Vector2(25, 16));
	delete renderer; 
	std::vector<Vector2> deltas { 
		Vector2(0, 0), 
		Vector2(32, 0), 
		Vector2(32 * 2, 0)
	};
	animImageRenderer = new AnimatedImageRenderer(&transform, Vector2(5, 6), Vector2(25, 16), deltas, true, 3); 
	renderer = animImageRenderer; 
	// RIGID BODY 
	rb = new RigidBody(&transform);
	Vector2 topLeft = transform.position - transform.size / 2;
	rb->AddCollision(new AABB(topLeft, transform.size));
	rb->SetLinearDrag(7);
}

void Player::Update(float dt)
{
	Object::Update(dt); 

	animImageRenderer->Update(dt); 

	lastFireTime += dt;

	MovementInputs();

	ShootInputs(); 
}

void Player::MovementInputs()
{
	Vector2 inputForce = Vector2();

	//VERTICAL
	if (IM.CheckKeyState(SDLK_UP, HOLD))
		inputForce.y -= 1;
	if (IM.CheckKeyState(SDLK_DOWN, HOLD))
		inputForce.y += 1;
	//HORIZONTAL
	if (IM.CheckKeyState(SDLK_LEFT, HOLD))
		inputForce.x -= 1;
	if (IM.CheckKeyState(SDLK_RIGHT, HOLD))
		inputForce.x += 1;

	inputForce.Normalize();
	inputForce = inputForce * force;
	AddMovement(inputForce);
}

void Player::Shoot()
{
	if (lastFireTime >= fireTime)
	{
		lastFireTime = 0;
		SPAWNER.SpawnObject(new PlayerBullet(transform.position));
	}
}

void Player::ShootInputs()
{
	if (IM.CheckKeyState(SDLK_SPACE, HOLD))
		Shoot();
}
