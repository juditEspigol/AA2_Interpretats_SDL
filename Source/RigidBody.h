#pragma once
#include "Transform.h"
#include "AABB.h"
#include <vector>

class RigidBody
{
private:
	std::vector<AABB*> colliders; 
	Transform* transform; 
	Vector2 velocity; 
	float angularVelocity; 

	Vector2 acceleration; 
	float angularAcceleration; 

	float linearDrag; 
	float angularDrag; 

public:
	RigidBody(Transform* t)
		: transform(t), velocity(Vector2()), angularVelocity(0.0f), 
		acceleration(Vector2()), angularAcceleration(0.0f), 
		linearDrag(0.0f), angularDrag(0.0f) 
	{}

	// Collision
	inline void AddCollision(AABB* collider)
	{
		colliders.push_back(collider); 
	}
	inline bool CheckCollision(const RigidBody* other)
	{
		for (AABB* col : colliders)
		{
			for (AABB* otherCol : other->colliders)
			{
				if (col->CheckOverlappingAABB(*otherCol))
					return true; 
			}
		}
		return false;
	}
	inline bool CheckOverlappingPoint(Vector2 point)
	{
		for (AABB* col : colliders)
		{
			if (col->CheckOverlappingPoint(point))
				return true; 
		}
		return false; 
	}

	// Movement 
	void Update(float dt); 
	inline void AddForce(Vector2 force)
	{
		velocity = velocity + force; 
	}
	inline void AddTorque(float amount)
	{
		angularVelocity += amount; 
	}

	inline Vector2 GetVelocity() { return velocity; }
	inline void SetVeclocity(Vector2 _velocity) { velocity = _velocity; }
	inline void SetLinearDrag(float amount) { linearDrag = amount; }
	inline void SetAngularDrag(float amount) { angularDrag = amount; }
};

