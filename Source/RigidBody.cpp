#include "RigidBody.h"

void RigidBody::Update(float dt)
{
	// Update de la velocitat
	velocity = velocity + acceleration * dt;
	angularVelocity = angularVelocity + angularAcceleration * dt; 

	// BOX 2D DRAG
	velocity = velocity * (1.0 / (1.0 + dt * linearDrag));
	angularVelocity = angularVelocity * (1.0 / (1.0 + dt * angularDrag));

	// Update position
	transform->position = transform->position + velocity * dt; 
	transform->angle = transform->angle + angularVelocity * dt; 

	// Move the AABB
	for (AABB* collider : colliders)
	{
		collider->SetSize(transform->size * transform->scale);
		collider->SetTopLeft(transform->position);
		if (transform->centered)
			collider->SetTopLeft(collider->GetTopLeft() - collider->GetSize() / 2.0f); 
	}
}
