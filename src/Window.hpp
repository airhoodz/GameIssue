#ifndef Window_hpp
#define Window_hpp

#include <SFML/Graphics.hpp>

class Window
{
public:
    Window(const std::string& windowName);
    
    void Update();
    
    void BeginDraw();
    void Draw(const sf::Drawable& drawable);
	void Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type);
	void EndDraw();
    
    sf::Vector2u GetCenter() const;
    sf::FloatRect GetViewSpace() const;
    
    bool IsOpen() const;

	const sf::View& GetView() const;
	void SetView(const sf::View& view);
    
private:
    sf::RenderWindow window;
};

#endif /* Window_hpp */
