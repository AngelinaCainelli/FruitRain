#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
using namespace sf;
class Game;

class Scene {
public:
	Scene();
	virtual void update(Game &game)=0;
	virtual void draw()=0;
	virtual void processEvent(sf::Event &ev);
	~Scene();
protected:
	RenderWindow* w;
	Event ev;
};

#endif

