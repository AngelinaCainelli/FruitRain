#ifndef HEART_H
#define HEART_H
#include "Entity.h"
#include "Heart.h"

class Heart:public Entity{
public:
	Heart(int pos_x, int pos_y, Texture &t);
	void update() override;
	void draw(RenderWindow &w) override;
	const int& getLifePoints();
	~Heart();
private:
	int lifePoints;
};

#endif

