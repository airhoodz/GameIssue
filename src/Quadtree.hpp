#ifndef Quadtree_hpp
#define Quadtree_hpp

#include <memory>
#include <vector>

#include "C_BoxCollider.hpp"
#include "Object.hpp"
#include "Debug.hpp"


class Quadtree
{
public:
	Quadtree();
	Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree* parent);

	//insert object into quadtree
	void Insert(std::shared_ptr<C_BoxCollider> object);

	//remove object from quadtree when no longer needed
	void Remove(std::shared_ptr<C_BoxCollider> object);

	//Clear quadtree
	void Clear();

	//Draw debug items
	void DrawDebug();

	void UpdatePosition(std::shared_ptr<C_BoxCollider> object);

	//return vector that intersects search area
	std::vector<std::shared_ptr<C_BoxCollider>> Search(const sf::FloatRect& area);
	

	//returns bounds of current node
	const sf::FloatRect& GetBounds() const;

private:
	void Search(const sf::FloatRect& area, std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects);

	//return index for node that contains the object. -1 if this node
	int GetChildIndexForObject(const sf::FloatRect& objectBounds);

	//create child node
	void Split();

	//indices for array of children
	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	int maxObjects;
	int maxLevels;

	//base node
	Quadtree* parent;
	std::shared_ptr<Quadtree> children[4];

	//store objects in this node
	std::vector<std::shared_ptr<C_BoxCollider>> objects;

	//variable for how deep current node is from base node
	int level;

	//bounds of node
	sf::FloatRect bounds;
};

#endif

