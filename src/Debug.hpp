#ifndef Debug_hpp
#define Debug_hpp

#include <array>
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Input.hpp"

class Debug
{
public:
	static void Draw(Window& window);

	static void DrawRect(const sf::FloatRect& rect, sf::Color color = sf::Color::White);

	static void DrawLine(const sf::Vector2f& from, const sf::Vector2f& to, sf::Color color = sf::Color::White);

	static void Log(const std::string& msg);
	static void LogWarning(const std::string& msg);
	static void LogError(const std::string& msg);

	static void HandleCameraZoom(Window& window, Input& input);

private:
	static std::vector<std::array<sf::Vertex, 2>> lines;
	static std::vector<sf::RectangleShape> rects;
};

#endif