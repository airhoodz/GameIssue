#ifndef C_RemoveObjectOnCollisionEnter_hpp
#define C_RemoveObjectOnCollisionEnter_hpp

#include "Component.hpp"
#include "C_Collidable.hpp"
#include "SharedContext.hpp"


class C_RemoveObjectsOnCollisionEnter : public Component, public C_Collidable
{
public:
	C_RemoveObjectsOnCollisionEnter(Object* owner);

	void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other) override;
};

#endif

