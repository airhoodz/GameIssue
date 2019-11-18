#ifndef Component_hpp
#define Component_hpp

#include "Window.hpp"

class Object;

class Component
{
public:
	Object* owner;
    Component(Object* owner) : owner(owner){}
    
    virtual void Awake() {};
    virtual void Start() {};
    
    virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
    
protected:
    
};

#endif /* Component_hpp */
