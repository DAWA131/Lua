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
	float Xspeed;
};

struct Jumping
{
	float ySpeed;
};

struct Player
{
	bool NonVoidStruct;
};

struct Drawable
{
	sf::CircleShape shape;

	Drawable() : shape(5.f)
	{
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(400, 750);
	}
};