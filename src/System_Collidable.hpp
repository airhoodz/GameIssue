#ifndef System_Collidable_hpp
#define System_Collidable_hpp

#include <vector>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "Object.hpp"
#include "Quadtree.hpp"
#include "Bitmask.hpp"
#include "ComponentPairHash.hpp"

class System_Collidable
{
public:
	System_Collidable();

	void Add(std::vector<std::shared_ptr<Object>>& objects);
	void ProcessRemovals();
	void UpdatePositions(std::vector<std::shared_ptr<Object>>& objects);
	void Update();
	void Resolve();

private:
	void ProcessCollidingObjects();

	//Used to store collision layer data - which layers can collide
	std::unordered_map<CollisionLayer, Bitmask> collisionLayers;

	//stores all collidables along with layer
	std::unordered_map<CollisionLayer, std::vector<std::shared_ptr<C_BoxCollider>>> collidables;

	std::unordered_set<std::pair<std::shared_ptr<C_BoxCollider>, std::shared_ptr<C_BoxCollider>>, ComponentPairHash> objectsColliding;

	//Quadtree stores collidables
	Quadtree collisionTree;
};

#endif

