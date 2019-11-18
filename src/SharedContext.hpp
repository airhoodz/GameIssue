#ifndef SharedContext_hpp
#define SharedContext_hpp

#include "Input.hpp"
#include "WorkingDirectory.hpp"
#include "ResourceAllocator.hpp"
#include "Window.hpp"

class ObjectCollection;
class Quadtree;
class Object;

struct SharedContext
{
	Input* input;
	ObjectCollection* objects;
	WorkingDirectory* workingDir;
	ResourceAllocator<sf::Texture>* textureAllocator;
	Window* window;
	Quadtree* collisionTree;
};

#endif


