#include "Player.h"

// OnCollisionEnter
#include "EnemyPlane.h"
#include "EnemyBullet.h"

Player::Player()
{
	isPendingDestroy = false;

	// PLAYER SETTINGS 
	isRolling = false;
	force = 40; 

	health = 3;
	iFrames = 1.00f;
	lastIFrames = iFrames;

	fireTime = 0.15f;
	lastFireTime = fireTime;
	doubleFire = false;

	// TRANSFORM
	transform = new Transform();
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.75);
	transform->angle = 0.0f;
	transform->scale = Vector2(2.0f, 2.0f);
	transform->size = Vector2(16, 16);

	// RENDER
	CreateAnimations(); 
	renderer = renderers["Idle"]; 

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void Player::CreateAnimations()
{
	renderers.emplace("Idle", new ImageRenderer(transform, Vector2(5, 6), Vector2(25, 16)));
	std::vector<Vector2> rightDeltas {
		Vector2(32, 0),
		Vector2(32 * 3, 0),
		Vector2(32 * 5, 0)
	};
	renderers.emplace("Right", new AnimatedImageRenderer(transform, Vector2(5, 6), Vector2(25, 16), rightDeltas, false, 20));
	std::vector<Vector2> leftDeltas {
		Vector2(32 * 2, 0),
		Vector2(32 * 4, 0),
		Vector2(32 * 6, 0)
	};
	renderers.emplace("Left", new AnimatedImageRenderer(transform, Vector2(5, 6), Vector2(25, 16), leftDeltas, false, 20));
}

void Player::Update(float dt)
{
	GameObject::Update(dt); 

	lastIFrames += dt;

	lastFireTime += dt;
	ShootInputs();

	MovementInputs();
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
	{
		inputForce.x -= 1;
		ChangeAnimation("Left"); 
	}
	else if (IM.CheckKeyState(SDLK_RIGHT, HOLD))
	{
		inputForce.x += 1;
		ChangeAnimation("Right");
	}
	else
	{
		ChangeAnimation("Idle");
	}


	inputForce.Normalize();
	inputForce = inputForce * force;
	AddMovement(inputForce);
}

void Player::Shoot()
{
	if (lastFireTime >= fireTime)
	{
		lastFireTime = 0;
		SPAWNER.SpawnObject(new PlayerBullet(Vector2(transform->position.x + 5, transform->position.y)));
		SPAWNER.SpawnObject(new PlayerBullet(Vector2(transform->position.x - 5, transform->position.y)));
	}
}

void Player::ShootInputs()
{
	if (IM.CheckKeyState(SDLK_SPACE, HOLD))
		Shoot();
}

void Player::EnableDoubleFire()
{
}

void Player::OnCollisionEnter(Object* other)
{
	if (rb->CheckCollision(other->GetRigidBody()))
	{
		if (IsEnemyPlane(other))
			return;
		if (IsEnemyBullet(other))
			return;
	}
}

bool Player::IsEnemyPlane(Object* other)
{
	if (dynamic_cast<EnemyPlane*>(other))
	{
		GetDamage(1);
		return true;
	}

	return false; 
}
bool Player::IsEnemyBullet(Object* other)
{
	if (dynamic_cast<EnemyBullet*>(other))
	{
		GetDamage(1);
		other->Destroy();
		return true;
	}
	return false;
}

void Player::GetDamage(const int amount)
{
	if (lastIFrames >= iFrames)
	{
		lastIFrames = 0;
		health -= amount;

		if (health <= 0)
			Destroy();
	}
}
