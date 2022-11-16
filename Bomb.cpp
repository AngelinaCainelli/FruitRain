#include "Bomb.h"

Bomb::Bomb(int pos_x, int pos_y, Texture &t){
	//Constructor
	this->sprite.setTexture(t);
	this->sprite.setScale(0.15,0.15);
	this->sprite.setPosition(pos_x,pos_y);
	damage=20;
	
}

const int& Bomb::getDamage(){
	//Retorna el valor del da;o
	return this->damage;
}

void Bomb::update(){
	//Movimiento de la bomba
	this->sprite.move(0,movementSpeed*1.5);
}


void Bomb::draw(RenderWindow &w){
	w.draw(this->sprite);
}

Bomb::~Bomb() {
	
}

