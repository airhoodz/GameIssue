#include "C_ProjectileAttack.hpp"
#include "Object.hpp"

std::unordered_map<FacingDirection, sf::IntRect> C_ProjectileAttack::textureDirectionBindings = {};
std::unordered_map<FacingDirection, sf::Vector2f> C_ProjectileAttack::offsetDirectionBindings = {};
std::unordered_map<FacingDirection, sf::Vector2f> C_ProjectileAttack::velocityDirectionBindings = {};

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner), projectileVelocity(400.f) {}

void C_ProjectileAttack::Awake()
{
	direction = owner->GetComponent<C_Direction>();
	animation = owner->GetComponent<C_Animation>();
}

void C_ProjectileAttack::Update(float deltaTime)
{
	// Use the input class from shared context.
	if (owner->context->input->IsKeyDown(Input::Key::E))
	{
		animation->SetAnimationState(AnimationState::Projectile);
	}
	// Use the input class from shared context.
	else if (owner->context->input->IsKeyUp(Input::Key::E))
	{
		animation->SetAnimationState(AnimationState::Idle);
	}
}


void C_ProjectileAttack::Start()
{
	projectileTextureID = owner->context->textureAllocator->Add(owner->context->workingDir->Get() + "arrow.png");

	textureDirectionBindings.emplace(FacingDirection::Up, sf::IntRect(0, 0, 64, 64));
	textureDirectionBindings.emplace(FacingDirection::Left, sf::IntRect(64, 0, 64, 64));
	textureDirectionBindings.emplace(FacingDirection::Down, sf::IntRect(128, 0, 64, 64));
	textureDirectionBindings.emplace(FacingDirection::Right, sf::IntRect(192, 0, 64, 64));

	//Offsets for arrow starting location
	offsetDirectionBindings.emplace(FacingDirection::Up, sf::Vector2f());
	offsetDirectionBindings.emplace(FacingDirection::Left, sf::Vector2f(-8.f, 3.f));
	offsetDirectionBindings.emplace(FacingDirection::Down, sf::Vector2f(-3.f, 15.f));
	offsetDirectionBindings.emplace(FacingDirection::Right, sf::Vector2f(8.f, 3.f));

	//initial settings for velocity based on directions
	velocityDirectionBindings.emplace(FacingDirection::Up, sf::Vector2f(0.f, -1.f));
	velocityDirectionBindings.emplace(FacingDirection::Left, sf::Vector2f(-1.f, 0.f));
	velocityDirectionBindings.emplace(FacingDirection::Down, sf::Vector2f(0.f, 1.f));
	velocityDirectionBindings.emplace(FacingDirection::Right, sf::Vector2f(1.f, 0.f));

	animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Up, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));

	animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Left, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
	animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Down, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
	animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Right, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
}

void C_ProjectileAttack::SpawnProjectile()
{
	//Get current facing direction
	FacingDirection faceDir = direction->Get();

	//Create new object for projectile
	std::shared_ptr<Object> projectile = std::make_shared<Object>(owner->context);

	//Set objects position
	projectile->transform->SetPosition(owner->transform->GetPosition() + offsetDirectionBindings.at(faceDir));

	//Add sprite to object
	auto projSprite = projectile->AddComponent<C_Sprite>();
	projSprite->Load(projectileTextureID);
	projSprite->SetDrawLayer(DrawLayer::Entities);
	projSprite->SetSortOrder(100);
	projSprite->SetTextureRect(textureDirectionBindings.at(faceDir));

	auto velocity = projectile->AddComponent<C_Velocity>();
	velocity->Set(velocityDirectionBindings.at(faceDir) * projectileVelocity);

	//Add collider to any projectiles spawned here
	auto collider = projectile->AddComponent<C_BoxCollider>();
	collider->SetSize(32, 32);
	collider->SetLayer(CollisionLayer::Projectile);

	//Add component to remove object when it collides
	projectile->AddComponent<C_RemoveObjectsOnCollisionEnter>();

	// Use the object collection class from shared context.
	owner->context->objects->Add(projectile);
}

