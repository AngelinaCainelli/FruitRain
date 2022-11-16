#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "Player.h"
using namespace std;

class Player : public Entity {
public:
	Player();
	void update() override;
	void draw(RenderWindow &w) override;
	Sprite &getSprite();
	void setPos(const float x, const float y);
	void setPos(Vector2f pos);
	void setSpeed(int s);
	void setHp(int dmg);
	const int getHp() const;
	const int getHpMax() const;
	const Vector2f getPos();
	Texture vCharTex[2];
	bool isAlive();
private:
	bool isIdle;
	int hp;
	int hpMax;
	int speed;
	
	
};

#endif

