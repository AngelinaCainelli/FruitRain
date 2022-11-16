#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace std;
using namespace sf;

class Entity {
public:
	virtual void update()=0;
	virtual void draw(RenderWindow &w)=0;
	const FloatRect getBounds() const;
	Entity();
	~Entity();
protected:
	Texture texture;
	Sprite sprite;

	float movementSpeed;
	
};

#endif

