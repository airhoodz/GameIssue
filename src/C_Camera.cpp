#include "C_Camera.hpp"
#include "Object.hpp"

C_Camera::C_Camera(Object* owner) : Component(owner) {}

void C_Camera::LateUpdate(float deltaTime)
{
	// Use the Window class from shared context.
	sf::View view = owner->context->window->GetView();

	const sf::Vector2f& targetPos = owner->transform->GetPosition();
	view.setCenter(targetPos.x, targetPos.y);

	// Use the Window class from shared context.
	owner->context->window->SetView(view);
}
