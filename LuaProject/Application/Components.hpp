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
	float xSpeed;
	float ySpeed;
	bool setPos;
};

struct Jumping
{
	float direction;
	float height;
};

struct Stopping
{
	bool NonVoidStruct;
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
public:
	sf::Sprite sprite;
	sf::Texture tex;

	Drawable(std::string texName, float x = 0, float y = 0)
	{
		tex.loadFromFile(texName);
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
	}
};