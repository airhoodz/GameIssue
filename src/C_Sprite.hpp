#ifndef C_Sprite_hpp
#define C_Sprite_hpp

#include "Component.hpp"
#include "C_Transform.hpp"
#include "ResourceAllocator.hpp"
#include "C_Drawable.hpp"

class C_Sprite : public Component, public C_Drawable
{
public:
    C_Sprite(Object* owner);

    void Load(int id);
    void Load(const std::string& filePath);
    
    void LateUpdate(float deltaTime) override;
    void Draw(Window& window) override;
    
    void SetTextureRect(int x, int y, int width, int height);
    void SetTextureRect(const sf::IntRect& rect);
	
	bool ContinueToDraw() const override;
    
    void SetScale(float x, float y);
    
private:
    sf::Sprite sprite;
    int currentTextureID;
};

#endif /* C_Sprite_hpp */
