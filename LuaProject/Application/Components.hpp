#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Health
{
	float Value;
};

struct Poison
{
	float TickDamage;
};

struct Moving
{
	float x;
};

struct drawable
{
	sf::CircleShape shape;

	drawable() : shape(100.f)
	{
		shape.setFillColor(sf::Color::Green);
	}
};