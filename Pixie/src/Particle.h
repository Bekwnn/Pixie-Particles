#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
class Emitter;

class Particle
{
public:
	Emitter* emitter;
	sf::Sprite sprite;	//has color, position
	sf::Vector2f velocity;
	float rotationalVelocity;
	float life;
	
public:

	Particle(Emitter &parent, sf::Texture &tex);

	void Update(sf::RenderWindow &window, float deltaTime);

	void Draw(sf::RenderWindow &window);
};

#endif