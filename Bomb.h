#ifndef BOMB_H
#define BOMB_H
#include "Entity.h"
#include "Bomb.h"

class Bomb:public Entity {
public:
	Bomb(int pos_x, int pos_y, Texture &t);
	const int& getDamage();
	void update() override;
	void draw(RenderWindow &w) override;
	~Bomb();
private:
	int damage;
};

#endif

