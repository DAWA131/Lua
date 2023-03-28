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
	bool setPos;
};

struct Jumping
{
	float ySpeed;
};

struct Player
{
	bool NonVoidStruct;
};

struct Collidable
{
	bool collide;
};

struct Drawable
{
	sf::Sprite sprite;
	sf::Texture tex;

	Drawable(std::string texName, float x = 0, float y = 0)
	{
		tex.loadFromFile(texName);
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
	}
};