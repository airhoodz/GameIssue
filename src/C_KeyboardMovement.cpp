#include "C_KeyboardMovement.hpp"
#include "Object.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object* owner) : Component(owner), moveSpeed(300.f) {}

void C_KeyboardMovement::Awake()
{
	animation = owner->GetComponent<C_Animation>();
    velocity = owner->GetComponent<C_Velocity>();
}


void C_KeyboardMovement::SetMovementSpeed(float moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void C_KeyboardMovement::Update(float deltaTime)
{
	if (animation->GetAnimationState() == AnimationState::Projectile)
	{
		velocity->Set(0.f, 0.f);
		return;
	}

	float xMove = 0.f;

	// Use input class from shared context.
	if (owner->context->input->IsKeyPressed(Input::Key::Left))
	{
		xMove = -moveSpeed;
	}
	// Use input class from shared context.
	else if (owner->context->input->IsKeyPressed(Input::Key::Right))
	{
		xMove = moveSpeed;
	}

	float yMove = 0.f;
	// Use input class from shared context.
	if (owner->context->input->IsKeyPressed(Input::Key::Up))
	{
		yMove = -moveSpeed;
	}
	// Use input class from shared context.
	else if (owner->context->input->IsKeyPressed(Input::Key::Down))
	{
		yMove = moveSpeed;
	}

	velocity->Set(xMove, yMove);
}
