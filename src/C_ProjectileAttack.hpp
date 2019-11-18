#ifndef C_ProjectileAttack_hpp
#define C_ProjectileAttack_hpp

#include <unordered_map>

#include "Component.hpp"
#include "C_Animation.hpp"
#include "Input.hpp"
#include "ObjectCollection.hpp"
#include "WorkingDirectory.hpp"
#include "C_RemoveObjectsOnCollisionEnter.hpp"


class C_ProjectileAttack : public Component
{
public:
	C_ProjectileAttack(Object* owner);

	void Awake() override;

	void Update(float deltaTime) override;


	void Start() override;

	

private:
	int projectileTextureID;
	float projectileVelocity;

	void SpawnProjectile();

	std::shared_ptr<C_Animation> animation;
	std::shared_ptr<C_Direction> direction;

	static std::unordered_map<FacingDirection, sf::IntRect> textureDirectionBindings;
	static std::unordered_map<FacingDirection, sf::Vector2f> offsetDirectionBindings;
	static std::unordered_map<FacingDirection, sf::Vector2f> velocityDirectionBindings;
};

#endif

