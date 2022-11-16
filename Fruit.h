#ifndef FRUIT_H
#define FRUIT_H
#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>

class Fruit : public Entity{
public:
	Fruit(float pos_x, float pos_y,Texture &t, int option, float speed);
	void update() override;
	void draw(RenderWindow &w) override;
	
	const int& getType() const;
	const int& getPoints() const;
	~Fruit();
private:
	int points;
	int type;
	float speed;
};

#endif

