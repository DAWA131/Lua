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

struct Position
{
	float xPos;
	float yPos;
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