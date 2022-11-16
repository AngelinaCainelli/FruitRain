#include "Fruit.h"

Fruit::Fruit(float pos_x, float pos_y,Texture &t,int option, float speed) {
	//Constructor

	this->sprite.setTexture(t);
	this->sprite.setScale(0.25,0.25);
	this->sprite.setPosition(pos_x,pos_y);
	
	this->type=option;
	this->speed=speed;
	
	if(option==0) this->points= 10;
	if(option==1) this->points= 15;
	if(option==2) this->points= 20;
}

Fruit::~Fruit() {
	
}

const int& Fruit::getType() const{
	//Retorna tipo
	return this->type;
}
	
const int& Fruit::getPoints() const{
	//Retorna puntos
	return this->points;
}

void Fruit::update(){
	//Movimiento de las frutas
	this->sprite.move(0,(movementSpeed/2)*speed);
}

void Fruit::draw(RenderWindow &w){
	w.draw(this->sprite);
}
