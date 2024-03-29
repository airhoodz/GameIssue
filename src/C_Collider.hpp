#ifndef C_Collider_hpp
#define C_Collider_hpp

#include <memory>
#include <SFML/Graphics.hpp>

#include "Bitmask.hpp"
#include "Component.hpp"

//enum ints used for defining collision layers
enum class CollisionLayer
{
	Default = 1, // bit 0
	Player = 2, // bit 1
	Tile = 3,    // bit 2
	Projectile = 4 // bit 3

};

struct Manifold
{
	bool colliding = false;
	const sf::FloatRect* other;
};

class C_Collider : public Component
{
public:
	C_Collider(Object* owner);
	~C_Collider();

	virtual Manifold Intersects(std::shared_ptr<C_Collider> other) = 0;
	virtual void ResolveOverlap(const Manifold& m) = 0;

	bool IsTrigger() const;
	void SetTrigger(bool isTrigger);

	CollisionLayer GetLayer() const;
	void SetLayer(CollisionLayer layer);

private:
	bool isTrigger;
	CollisionLayer layer;
};

#endif