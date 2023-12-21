#include "Player.h"

// OnCollisionEnter
#include "EnemyPlane.h"
#include "EnemyBullet.h"

Player::Player()
{
	isPendingDestroy = false;

	currentState = FLYING;

	health = LIVES_GAME.GetLives();
	force = 40; 
	fireTime = 0.15f;
	lastFireTime = fireTime;

	doubleFire = false;

	// TRANSFORM
	transform = new Transform();
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y + 155);
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

	// RIGHT & LEFT
	std::vector<Vector2> leftDeltas {
		Vector2(32 * 2, 0),
		Vector2(32 * 4, 0),
		Vector2(32 * 6, 0)
	};
	renderers.emplace("Right", new AnimatedImageRenderer(transform, Vector2(5, 6), Vector2(25, 16), leftDeltas, false, 20, SDL_FLIP_HORIZONTAL));
	renderers.emplace("Left", new AnimatedImageRenderer(transform, Vector2(5, 6), Vector2(25, 16), leftDeltas, false, 20));
	// DEATH
	DeathAnimation(); 
	//ROLL
	RollAnimation(); 
}

void Player::Update(float dt)
{
	GameObject::Update(dt); 
	UpdateSupportPlanes(dt);
	lastFireTime += dt; 

	lastFireTime += dt; 

	CheckStatePlayer(); 
}

void Player::CheckStatePlayer()
{
	switch (currentState)
	{
	case FLYING:
		MoveInputs();
		ShootInputs();
		UpdateFlyingAnimation();
		break;

	case LANDED:
		rb->SetVeclocity(Vector2(0, -18));
		break;

	case ROLLING:
		MoveInputs();
		Roll(); 
		break;

	case DEATH:
		Death(); 
		break;

	default:
		break;
	}
}

void Player::ChangeState(const StatesPlayer newState)
{
	switch (currentState)
	{
	case FLYING:
		break;
	case LANDED:
		rb->SetVeclocity(Vector2());
		break;
	case ROLLING:
		break;
	case DEATH:
		break;
	case COUNT:
		break;
	default:
		break;
	}

	switch (newState)
	{
	case FLYING:
		break;
	case LANDED:
		break;
	case ROLLING:
		break;
	case DEATH:
		break;
	case COUNT:
		break;
	default:
		break;
	}

	currentState = newState;
}

void Player::MoveInputs() 
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

	//ROLL
	if (IM.CheckKeyState(SDLK_x, PRESSED))
		currentState = ROLLING; 

	inputForce.Normalize();
	inputForce = inputForce * force;
	AddMovement(inputForce); 
}
void Player::UpdateFlyingAnimation()
{
	if (IM.CheckKeyState(SDLK_LEFT, HOLD))
	{
		ChangeAnimation("Left");
		for (auto supportPlane : supportPlanes)
			if (supportPlane->GetIsLocated())
				supportPlane->ChangeAnimation("Left");
	}
	else if (IM.CheckKeyState(SDLK_RIGHT, HOLD))
	{
		ChangeAnimation("Right");
		for (auto supportPlane : supportPlanes)
			if (supportPlane->GetIsLocated())
				supportPlane->ChangeAnimation("Right");
	}
	else
	{
		ChangeAnimation("Idle");
		for (auto supportPlane : supportPlanes)
			if (supportPlane->GetIsLocated())
				supportPlane->ChangeAnimation("Idle");
	}
}

void Player::ShootInputs()
{
	if (IM.CheckKeyState(SDLK_SPACE, HOLD))
		Shoot(); 
}
void Player::Shoot()
{
	if (lastFireTime >= fireTime)
	{
		lastFireTime = 0;
		SPAWNER.SpawnObject(new PlayerBullet(Vector2(transform->position.x + 4, transform->position.y)));
		SPAWNER.SpawnObject(new PlayerBullet(Vector2(transform->position.x - 4, transform->position.y)));

		// DOUBLE SHOOT
		if (doubleFire)
		{
			SPAWNER.SpawnObject(new PlayerBullet(Vector2(transform->position.x + 11, transform->position.y + 3)));
			SPAWNER.SpawnObject(new PlayerBullet(Vector2(transform->position.x - 11, transform->position.y + 3)));
		}
		//SUPPORT PLANES SHOOT
		for (auto supportPlane : supportPlanes)
			supportPlane->Shoot();
	}
}

void Player::Death()
{
	ChangeAnimation("Death");
	if (renderer->LastFrame())
	{
		transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.75);
		if (health <= 0)
			Destroy();

		currentState = FLYING;
	}
}
void Player::DeathAnimation()
{
	std::vector<Vector2> deltas{
		Vector2(0, 0),
		Vector2(33, 0),
		Vector2(33 * 2, 0),
		Vector2(33 * 3, 0),
		Vector2(33 * 4, 0),
		Vector2(33 * 5, 0),
		Vector2(293, 0)
	};
	renderers.emplace("Death", new AnimatedImageRenderer(transform, Vector2(3, 101), Vector2(32, 32), deltas, false, 10));
}

void Player::Roll()
{
	ChangeAnimation("Roll");
	if (renderer->LastFrame())
		currentState = FLYING;
}
void Player::RollAnimation()
{
	std::vector<Vector2> deltas{
		Vector2(0, 0),
		Vector2(32, 0),
		Vector2(32 * 2, 0),
		Vector2(32 * 3, 0),
		Vector2(32 * 4, 0),
		Vector2(32 * 5, 0),
		Vector2(32 * 6, 0),
		Vector2(32 * 7, 0)
	};
	renderers.emplace("Roll", new AnimatedImageRenderer(transform, Vector2(4, 27), Vector2(28, 13), deltas, true, 15));
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
	if (currentState == FLYING)
	{
		health -= amount;
		LIVES_GAME.SubstractLives(1); 
	}
	currentState = DEATH;
}

void Player::AddSupportPlanes()
{
	// DELETE IF WE ALREADY HAVE PLANES
	if (!supportPlanes.empty())
	{
		for (auto supportPlane : supportPlanes)
			supportPlane->Destroy();

		supportPlanes.clear();
	}

	SupportPlane* support = new SupportPlane(true, transform->position);
	SPAWNER.SpawnObject(support);
	supportPlanes.push_back(support);

	SupportPlane* support2 = new SupportPlane(false, transform->position);
	SPAWNER.SpawnObject(support2);
	supportPlanes.push_back(support2);
}
void Player::UpdateSupportPlanes(float dt)
{
	for (int i = supportPlanes.size() - 1; i >= 0; i--)
	{
		if (supportPlanes[i]->IsPendingDestroy()) 
		{
			supportPlanes.erase(supportPlanes.begin() + i);
			continue;
		}
		supportPlanes[i]->LocatePlane(transform->position, dt);
	}
}
