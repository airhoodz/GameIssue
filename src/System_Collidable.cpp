#include "System_Collidable.hpp"

System_Collidable::System_Collidable() : collisionTree(5, 5, 0, { 0,0,4200,1080 }, nullptr)
{
	Bitmask defaultCollisions;
	defaultCollisions.SetBit((int)CollisionLayer::Default);
	collisionLayers.insert(std::make_pair(CollisionLayer::Default, defaultCollisions));

	collisionLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask(0)));

	Bitmask playerCollisions;
	playerCollisions.SetBit((int) CollisionLayer::Default);
	playerCollisions.SetBit((int) CollisionLayer::Tile);
	collisionLayers.insert(std::make_pair(CollisionLayer::Player, playerCollisions));

	Bitmask projectileCollisions;
	projectileCollisions.SetBit((int)CollisionLayer::Tile);
	collisionLayers.insert(std::make_pair(CollisionLayer::Projectile, projectileCollisions));

}

void System_Collidable::Add(std::vector<std::shared_ptr<Object>>& objects)
{
	for (auto o : objects)
	{
		auto collider = o->GetComponent<C_BoxCollider>();
		if (collider)
		{
			CollisionLayer layer = collider->GetLayer();

			auto itr = collidables.find(layer);

			if (itr != collidables.end())
			{
				collidables[layer].push_back(collider);
			}
			else
			{
				collidables.insert(std::make_pair(layer, std::vector<std::shared_ptr<C_BoxCollider>>{collider}));
			}
		}
	}
}

void System_Collidable::ProcessRemovals()
{
	for (auto layer : collidables)
	{
		auto itr = layer.second.begin();
		while (itr != layer.second.end())
		{
			if ((*itr)->owner->IsQueuedForRemoval())
			{
				//stop here
				
				itr = layer.second.erase(itr);
				
			}
			else
			{
				++itr;
			}
		}
	}
}

void System_Collidable::UpdatePositions(std::vector<std::shared_ptr<Object>>& objects)
{
	for (auto o : objects)
	{
		if (!o->transform->isStatic())
		{
			auto collider = o->GetComponent<C_BoxCollider>();

			if (collider)
			{
				collisionTree.UpdatePosition(collider);
			}
		}
	}

}



void System_Collidable::Resolve()
{
	for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
	{

		//if the layer collides with nothing then continue
		if (collisionLayers[maps->first].GetMask() == 0)
		{
			continue;
		}

		for (auto collidable : maps->second)
		{
			//if this collidable is static continue
			if (collidable->owner->transform->isStatic())
			{
				continue;
			}

			std::vector<std::shared_ptr<C_BoxCollider>> collisions = collisionTree.Search(collidable->GetCollidable());

			for (auto collision : collisions)
			{
				//check to make sure we are not resolving collisions between the same object
				if (collidable->owner->instanceID->Get() == collision->owner->instanceID->Get())
				{
					continue;
				}
				
				bool layersCollide = collisionLayers[collidable->GetLayer()].GetBit(((int)collision->GetLayer()));

				if (layersCollide)
				{
					Manifold m = collidable->Intersects(collision);

					if (m.colliding)
					{

						auto collisionPair = objectsColliding.emplace(std::make_pair(collidable, collision));

						if (collisionPair.second)
						{
							collidable->owner->OnCollisionEnter(collision);
							collision->owner->OnCollisionEnter(collidable);
						}

						if (collision->owner->transform->isStatic())
						{
							collidable->ResolveOverlap(m);
						}
						else
						{
							//Fix 2 - What if both objects aren't static?
							collidable->ResolveOverlap(m);
						}
					}
				}
			}
		}
	}
}

void System_Collidable::Update()
{
	collisionTree.DrawDebug();

	
	ProcessCollidingObjects();
	collisionTree.Clear();

	for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
	{
		for (auto collidable : maps->second)
		{
			collisionTree.Insert(collidable);
		}
	}

	Resolve();


}

void System_Collidable::ProcessCollidingObjects()
{
	auto itr = objectsColliding.begin();
	while (itr != objectsColliding.end())
	{
		auto pair = *itr;
		std::shared_ptr<C_BoxCollider> first = pair.first;
		std::shared_ptr<C_BoxCollider> second = pair.second;

		if (first->owner->IsQueuedForRemoval() || second->owner->IsQueuedForRemoval())
		{

			first->owner->OnCollisionExit(second);
			second->owner->OnCollisionExit(first);
			itr = objectsColliding.erase(itr);			

		}
		else
		{
			Manifold m = first->Intersects(second);

			if (!m.colliding)
			{
				first->owner->OnCollisionExit(second);
				second->owner->OnCollisionExit(first);

				itr = objectsColliding.erase(itr);
			}
			else
			{
				first->owner->OnCollisionStay(second);
				second->owner->OnCollisionStay(first);

				++itr;
			}
		}
	
	}
}