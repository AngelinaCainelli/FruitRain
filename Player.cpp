#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

Player::Player() {
	//Constructor
	vCharTex[0].loadFromFile("Assets/Images/char.png");
	vCharTex[1].loadFromFile("Assets/Images/charWalk.png");
	this->sprite.setTexture(vCharTex[0]);
	this->sprite.setScale(3,3);
	this->sprite.setOrigin(this->sprite.getTexture()->getSize().x*0.5, this->sprite.getTexture()->getSize().y*0.5);
	this->sprite.setPosition(400,560);
	hpMax = 200;
	hp = hpMax;
	speed=1;

	isIdle=true;
	
}

void Player::setPos(Vector2f pos){
	//modifica la posicion a partir de un Vector2f
	this->sprite.setPosition(pos);
}

void Player::setPos(const float x, const float y){
	//Modifica la posicion a partir de dos variables
	this->sprite.setPosition(x,y);
}

void Player::setSpeed(int s){
	//Modifica la velocidad
	this->speed=s;
}

void Player::setHp(int val){
	//Modifica el hp
	this->hp += val;
}

const int Player::getHp() const{
	//Retorna el hp
	return this->hp;
}

const int Player::getHpMax() const{
	//Retorna el hpMax
	return this->hpMax;
}

const Vector2f Player::getPos(){
	//Retorna la posicion
	return this->sprite.getPosition();
}

bool Player::isAlive(){
	//Retorna un booleano segun la vida del jugador
	if(hp<=0) return false;
	else return true;
}

void Player::update(){
	
	//Mover al personaje y cambiar direccion del sprite
	if(Keyboard::isKeyPressed(Keyboard::Left)){
		isIdle = false;
		this->sprite.setTexture(this->vCharTex[1]);
		this->sprite.setScale(3,3);
		this->sprite.move(-movementSpeed*speed,0);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Right)){
		isIdle=false;
		this->sprite.setTexture(this->vCharTex[1]);
		this->sprite.setScale(-3,3);
		this->sprite.move(movementSpeed*speed,0);
	}
	else isIdle=true;
	if(isIdle==true) this->sprite.setTexture(this->vCharTex[0]);
	
	
}

void Player::draw(RenderWindow &w){
	w.draw(this->sprite);
}
