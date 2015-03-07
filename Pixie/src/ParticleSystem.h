#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <SFML/Graphics.hpp>
#include <list>
#include "Emitter.h"

class ParticleSystem
{
public:
	sf::RenderWindow* window;
	std::list<Emitter*> emitters;
	sf::Rect<int> boundingBox;

public:
	
	ParticleSystem(sf::RenderWindow &win);
	
	ParticleSystem(sf::RenderWindow &win, sf::Rect<int> bounds);

	void AddEmitter(Emitter &emitter);

	void Update(float deltaTime);
	
	//calls Burst() on all emitters that can burst
	void Burst();
};

#endif