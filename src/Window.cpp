#include "Window.hpp"

Window::Window(const std::string& windowName) : window(sf::VideoMode(1920, 1080), windowName, sf::Style::Default)
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void Window::Update()
{
    sf::Event event;
    if (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Window::BeginDraw()
{
    window.clear(sf::Color::White);
}

void Window::Draw(const sf::Drawable& drawable)
{
    window.draw(drawable);
}

void Window::Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type)
{
	window.draw(vertices, vertexCount, type);
}

void Window::EndDraw()
{
    window.display();
}

sf::Vector2u Window::GetCenter() const
{
    sf::Vector2u size = window.getSize();
    
    return sf::Vector2u(size.x / 2, size.y / 2);
}

sf::FloatRect Window::GetViewSpace() const
{
	const sf::View& view = GetView();
    const sf::Vector2f viewCenter(window.getView().getCenter());
    const sf::Vector2f viewSize(window.getView().getSize());
    sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    
    return viewSpace;
}

bool Window::IsOpen() const
{
    return window.isOpen();
}

const sf::View& Window::GetView() const
{
	return window.getView();
}

void Window::SetView(const sf::View& view)
{
	window.setView(view);
}