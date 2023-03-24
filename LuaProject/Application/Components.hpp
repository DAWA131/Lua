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

struct Player
{
	bool NonVoidStruct;
};

struct Drawable
{
	sf::CircleShape shape;

	Drawable() : shape(100.f)
	{
		shape.setFillColor(sf::Color::Green);
	}
};