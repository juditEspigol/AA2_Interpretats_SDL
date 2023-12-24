#include "Player.h"

// OnCollisionEnter
#include "EnemyPlane.h"
#include "EnemyBullet.h"

Player::Player(ShipBackGround* _ship)
{
	isPendingDestroy = false;

	ship = _ship; 

	currentState = TAKE_OFF;
	nextState = FLYING; 

	health = LIVES_GAME.GetLives();
	force = 40; 
	fireTime = 1.0f;
	lastFireTime = fireTime;

	movementTime = 0.0f;
	movementState = 0;

	avaliableRolls = 3;

	doubleFire = false;

	shootID = AUDIO.LoadClip("Resources/Audio/PlayerShoot.wav");
	CollisionId = AUDIO.LoadClip("Resources/Audio/EnemyCollision.mp3");
	bulletId = AUDIO.LoadClip("Resources/Audio/BulletCollision.mp3");
	loseStageId = AUDIO.LoadClip("Resources/Audio/LoseStage.mp3");

	// TRANSFORM
	transform = new Transform();
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y);
	transform->angle = 0.0f;
	transform->scale = Vector2(2.0f, 2.0f);
	transform->size = Vector2(16, 16);

	// RENDER
	CreateAnimations(); 
	renderer = renderers["TakeOffImage"]; 

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
	//TAKE OFF
	TakeOffAnimation(); 
}

void Player::Update(float dt)
{
	GameObject::Update(dt); 
	UpdateSupportPlanes(dt);
	lastFireTime += dt; 

	lastFireTime += dt; 

	CheckStatePlayer(dt); 
}

void Player::CheckStatePlayer(float dt)
{
	switch (currentState)
	{
	case TAKE_OFF:
		movementTime += dt;
		TakeOff(); 
		break;

	case FLYING:

		if (!ship->GetPlayerCanLand())
		{
			MoveInputs();
			ShootInputs();
			UpdateFlyingAnimation();
		}
		else
		{
			ChangeAnimation("TakeOffImage"); 
			Vector2 positionToGo = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.75);
			Vector2 direction = positionToGo - transform->position; 

			if (direction.Magnitude() <= 1)
			{
				currentState = STOP; 
				SCORE.AddScore(5000);
			}
			else
			{
				Vector2 speed = Vector2();

				//VERTICAL
				if (transform->position.y < positionToGo.y) // support up, player down
					speed.y += 1;
				if (transform->position.y > positionToGo.y) // support down, player up
					speed.y -= 1;
				//HORITZONTAL
				if (transform->position.x < positionToGo.x) // support left, player right
					speed.x += 1;
				if (transform->position.x > positionToGo.x) // support right, player left
					speed.x -= 1;

				speed.Normalize();
				speed = speed * force;
				rb->AddForce(speed);
			}
		}
		break;

	case LANDED:
		rb->SetVeclocity(Vector2(0, -18));
		break;
	case ROLLING:
		if(nextState == FLYING)
			MoveInputs();
		Roll(nextState); 
		movementTime = 0; 
		break;

	case DEATH:
		Death(); 
		break;

	case STOP:
		if (IM.CheckKeyState(SDLK_SPACE, PRESSED))
		{
			ship->PlayerLanded();
			movementTime = 0;
			movementState = 0;
			currentState = TAKE_OFF;
			nextState = TAKE_OFF;
		}
		break; 

	default:
		break;
	}
}

void Player::MoveInputs() 
{ 
	Vector2 inputForce = Vector2();

	//VERTICAL
	if (transform->position.y - 18 >= 0 && IM.CheckKeyState(SDLK_UP, HOLD))
	{
		inputForce.y -= 1;
	}
	else if (transform->position.y - 18 <= 0)
	{
		rb->SetVeclocity(Vector2(0, 0));
		transform->position.y += 1;
	}
	

	if (transform->position.y + 18 <= RENDERER.GetSizeWindow().y && IM.CheckKeyState(SDLK_DOWN, HOLD))
	{
		inputForce.y += 1;
	}
	else if (transform->position.y + 18 >= RENDERER.GetSizeWindow().y)
	{
		rb->SetVeclocity(Vector2(0, 0));
		transform->position.y -= 1;
	}

	//HORIZONTAL
	if (transform->position.x - 18 >= 0 && IM.CheckKeyState(SDLK_LEFT, HOLD))
	{
		inputForce.x -= 1;
	}
	else if (transform->position.x - 18 <= 0)
	{
		rb->SetVeclocity(Vector2());
		transform->position.x += 1;
	}

	if (transform->position.x + 18 <= RENDERER.GetSizeWindow().x && IM.CheckKeyState(SDLK_RIGHT, HOLD))
	{
		inputForce.x += 1;
	}
	else if (transform->position.x + 18 >= RENDERER.GetSizeWindow().x)
	{
		rb->SetVeclocity(Vector2());
		transform->position.x -= 1;
	}


	//ROLL
	if (avaliableRolls > 0 && currentState == FLYING && IM.CheckKeyState(SDLK_x, PRESSED))
	{
		currentState = ROLLING; 
		avaliableRolls--;
	}

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
	if (IM.CheckKeyState(SDLK_z, PRESSED))
	{
		Shoot();
	}
	else if (IM.CheckKeyState(SDLK_z, HOLD))
	{
		if (lastFireTime >= fireTime)
		{
			Shoot(); 
		}
	}
}
void Player::Shoot()
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

	AUDIO.PlayClip(shootID);
	
}

void Player::Death()
{
	ChangeAnimation("Death");

	if (renderer->LastFrame())
	{
		doubleFire = false; 
		transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.75);
		if (health <= 0)
		{
			AUDIO.PlayClip(loseStageId);
			Destroy();
		}
		else
		{
			AUDIO.PlayClip(CollisionId);
		}

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

void Player::Roll(StatesPlayer nextState)
{
	ChangeAnimation("Roll");

	if (renderer->LastFrame())
	{
		movementState++;
		currentState = nextState;
	}
}
void Player::RollAnimation()
{
	std::vector<Vector2> deltas{
		Vector2(0, 0),
		Vector2(32, 0),
		Vector2(32 * 2, 0),
		Vector2(32 * 3, 0)
	};
	renderers.emplace("Roll", new AnimatedImageRenderer(transform, Vector2(4, 27), Vector2(28, 13), deltas, true, 5));
}

void Player::TakeOff()
{

	if (movementTime <= 1.0f && movementState == 0)
	{
		Vector2 newForce = Vector2(0, -0.5) * force;
		AddMovement(newForce);

		if (movementTime >= 0.5f && renderer != renderers["TakeOffAnimated"])
			ChangeAnimation("TakeOffAnimated");
	}
	else if (movementTime <= 0.75f && movementState == 1)
	{
		transform->angle = 180.0f;
		ChangeAnimation("Idle");
		Vector2 newForce = Vector2(0, 0.5) * force;
		AddMovement(newForce);
	}
	else if (movementTime <= 0.5 && movementState == 2)
	{
		transform->angle = 0.0f;
		ChangeAnimation("Idle");
		Vector2 newForce = Vector2(0, -0.5) * force;
		AddMovement(newForce);
	}
	else if (movementState == 0 || movementState == 1)
	{
		nextState = TAKE_OFF;
		currentState = ROLLING;
	}
	else
	{
		nextState = FLYING;
		currentState = FLYING;
	}
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
		if (currentState == ROLLING)
		{
			SCORE.AddScore(500);
			return true;
		}
		GetDamage(1);
		return true;
	}
	return false; 
}
bool Player::IsEnemyBullet(Object* other)
{
	if (dynamic_cast<EnemyBullet*>(other))
	{
		if (currentState == ROLLING)
		{
			SCORE.AddScore(500);
			return true;
		}
		AUDIO.PlayClip(bulletId);
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

void Player::LandingAnimation()
{
}

void Player::TakeOffAnimation()
{
	std::vector<Vector2> deltas{
		Vector2(0, 0),
		Vector2(20, 0),
		Vector2(20 * 2, 0)
	};
	renderers.emplace("TakeOffAnimated", new AnimatedImageRenderer(transform, Vector2(6, 84), Vector2(22, 16), deltas, false, 5));
	renderers.emplace("TakeOffImage", new ImageRenderer(transform, Vector2(6, 84), Vector2(22, 16)));
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
