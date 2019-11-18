#ifndef Object_hpp
#define Object_hpp

#include <vector>

#include "Window.hpp"
#include "Component.hpp"
#include "C_Transform.hpp"
#include "C_Drawable.hpp"
#include "C_InstanceID.hpp"
#include "SharedContext.hpp"
#include "C_Collidable.hpp"

class Object
{
public:
	Object(SharedContext* context);
    
    void Awake(); // Called when object created. Use to ensure required components are present.
    void Start(); // Called after Awake method. Use to initialise variables.
    
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

	//functions for collisions involving objects that inherit from C_Collidable
	void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other);
	void OnCollisionStay(std::shared_ptr<C_BoxCollider> other);
	void OnCollisionExit(std::shared_ptr<C_BoxCollider> other);
    
    template <typename T> std::shared_ptr<T> AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        // Check that that componenet does not exist
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        components.push_back(newComponent);

		//check if component is drawable
		if (std::dynamic_pointer_cast<C_Drawable>(newComponent))
		{
			drawable = std::dynamic_pointer_cast<C_Drawable>(newComponent);
		}

		if (std::dynamic_pointer_cast<C_Collidable>(newComponent))
		{
			collidables.push_back(std::dynamic_pointer_cast<C_Collidable>(newComponent));
		}
        
        return newComponent;
    };
    
    template <typename T> std::shared_ptr<T> GetComponent()
    {
      
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        return nullptr;
    };
    
    bool IsQueuedForRemoval();
    void QueueForRemoval();
	void UnqueueForRemoval();

	SharedContext* context;
    
    std::shared_ptr<C_Transform> transform;
	std::shared_ptr<C_Drawable> GetDrawable();
	std::shared_ptr<C_InstanceID> instanceID;
    
private:
	std::shared_ptr<C_Drawable> drawable;
    std::vector<std::shared_ptr<Component>> components;
	std::vector < std::shared_ptr<C_Collidable>> collidables;

    bool queuedForRemoval;
	
};


#endif /* Object_hpp */
