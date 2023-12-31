#pragma once
#include <string>
#include "Vector2.h"
#include "Transform.h"
#include "RigidBody.h"

class Object
{
protected:
	Transform* transform; 
	RigidBody* rb;
	bool isPendingDestroy; 

public:
	//TODO:: SourceOffset and sourceSize is form gameObject
	Object() = default; 
	virtual ~Object() 
	{
		delete rb; 
	}

	virtual void Render() = 0; 
	virtual void Update(float dt) 
	{
		rb->Update(dt); 
	};
	virtual void Destroy() { isPendingDestroy = true; }
	inline bool IsPendingDestroy() { return isPendingDestroy; }
	RigidBody* GetRigidBody() { return rb; }
	virtual void OnCollisionEnter(Object* other)
	{

	}

	// SETTERS & GETTERS
	inline void SetPosition(Vector2 _position) { transform->position = _position; }
	inline void SetScale(Vector2 _scale) { transform->scale = _scale; }
	inline void SetRotation(float _rotation) { transform->angle = _rotation; }

	inline Vector2 GetPosition() { return transform->position; }
	inline float GetRotation() { return transform->angle; }
	inline Vector2 GetScale() { return transform->scale; }
	inline Vector2 GetSize() { return transform->size; }
	inline Transform* GetTransform() { return transform; }
};


