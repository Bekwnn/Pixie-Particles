#include "Emitter.h"
#include "Particle.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>

Particle::Particle(Emitter &parent, sf::Texture &tex) : emitter(&parent)
{
	//TODO: create particle params struct and pass in more info
	sprite = sf::Sprite(tex);

	sprite.setColor(parent.color);

	sprite.setPosition(sf::Vector2f(
		parent.location.x(parent.generator),
		parent.location.y(parent.generator)
	));

	float scale = parent.initialScale(parent.generator);
	sprite.setScale(scale, scale);

	sprite.setRotation(parent.initialRotation(parent.generator));

	rotationalVelocity = parent.rotationVelocity(parent.generator);

	life = parent.lifetime;

	velocity = sf::Vector2f(
		parent.velocity.x(parent.generator),
		parent.velocity.y(parent.generator)
	);
}

void Particle::Update(sf::RenderWindow &window, float deltaTime)
{
	//printf("UpdatingParticle");
	life -= 1 * deltaTime;
	sprite.move(velocity * deltaTime);
	velocity += emitter->acceleration * deltaTime;
	sprite.rotate(rotationalVelocity * deltaTime);
	//TODO:
	//update color
	//update scale
	//update life
	Draw(window);
}

void Particle::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}