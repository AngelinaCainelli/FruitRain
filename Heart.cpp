#include "Heart.h"

Heart::Heart(int pos_x, int pos_y, Texture &t) {
	//Constructor
	this->sprite.setTexture(t);
	this->sprite.setScale(0.2,0.2);
	this->sprite.setPosition(pos_x,pos_y);
	lifePoints=15;
}

const int& Heart::getLifePoints(){
	//Retorna puntos de vida
	return this->lifePoints;
}



void Heart::update(){
	//Moviemiento del corazon
	this->sprite.move(0,movementSpeed*1.5);
}
void Heart::draw(RenderWindow &w){
	w.draw(this->sprite);
}


Heart::~Heart() {
	
}

