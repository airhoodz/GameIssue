#include "C_RemoveObjectsOnCollisionEnter.hpp"
#include "Object.hpp"

C_RemoveObjectsOnCollisionEnter::C_RemoveObjectsOnCollisionEnter(Object* owner) : Component(owner) {}

void C_RemoveObjectsOnCollisionEnter::OnCollisionEnter(std::shared_ptr<C_BoxCollider> other)
{
	//owner->QueueForRemoval();
	
}
