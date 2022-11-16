#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity() {
	//Constructor
	
	movementSpeed=5;
	
}

const FloatRect Entity::getBounds() const{
	return this->sprite.getGlobalBounds();
}

Entity::~Entity(){
	
}
