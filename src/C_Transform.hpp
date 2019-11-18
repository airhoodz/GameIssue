#ifndef C_Transform_hpp
#define C_Transform_hpp

#include "Component.hpp"

class C_Transform : public Component
{
public:
    C_Transform(Object* owner);

    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f& pos);
    
    void AddPosition(float x, float y);
    void AddPosition(sf::Vector2f pos);
    
    void SetX(float x);
    void SetY(float y);
    
    void AddX(float x);
    void AddY(float y);

	void SetStatic(bool isStatic);
	bool isStatic() const;
    
    const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetPreviousFramePosition() const;

private:
    sf::Vector2f position;
	bool isStaticTransform;
	sf::Vector2f previousFramePosition;
};

#endif /* C_Transform_hpp */
