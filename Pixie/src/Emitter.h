#ifndef EMITTER_H
#define EMITTER_H

#include <SFML/Graphics.hpp>
#include <list>
class ParticleSystem;
#include "Particle.h"

typedef std::uniform_real_distribution<float> UniformDistributionf;

struct UniformDistribution2f {
	std::uniform_real_distribution<float> x;
	std::uniform_real_distribution<float> y;

	UniformDistribution2f()
	{
		x = std::uniform_real_distribution<float>(0.0f, 0.0f);
		y = std::uniform_real_distribution<float>(0.0f, 0.0f);
	}

	UniformDistribution2f(sf::Vector2f min, sf::Vector2f max)
	{
		x = std::uniform_real_distribution<float>(min.x, max.x);
		y = std::uniform_real_distribution<float>(min.y, max.y);
	}

	UniformDistribution2f(sf::Vector2f fixedVal)
	{
		x = std::uniform_real_distribution<float>(fixedVal.x, fixedVal.x);
		y = std::uniform_real_distribution<float>(fixedVal.y, fixedVal.y);
	}
};

class Emitter
{
	std::list<Particle> particles;	//particles only accessed on iteration, forward_list may be better?
	int numParticlesAlive;
	float emissionCooldown;
	
public:
	ParticleSystem* particleSystem;
	sf::Texture* texture;	//texture used by all the sprites for this emitter
	std::minstd_rand generator;

	UniformDistribution2f velocity;
	UniformDistribution2f location;
	UniformDistributionf initialRotation;
	UniformDistributionf rotationVelocity;
	UniformDistributionf initialScale;
	
	sf::Color color = sf::Color::White;
	sf::Vector2f acceleration;
	
	int maxParticles;
	float emissionRate;
	float lifetime;
	bool bCanBurst;
	int burstAmount;
	
public:
	Emitter(sf::Texture &tex, float rate);

	void Update(sf::RenderWindow &window, float deltaTime);
	
	void Burst();
	
	void SetSpawnLocation(sf::Vector2f min, sf::Vector2f max)
	{ location = UniformDistribution2f(min, max); }

	void SetSpawnLocation(sf::Vector2f fixedvalue)
	{ location = UniformDistribution2f(fixedvalue); }
	
	void SetSpawnVelocity(sf::Vector2f min, sf::Vector2f max)
	{ velocity = UniformDistribution2f(min, max); }

	void SetSpawnVelocity(sf::Vector2f fixedvalue)
	{ velocity = UniformDistribution2f(fixedvalue); }

	void SetParticleSystem(ParticleSystem *ps)
	{ particleSystem = ps; }

	void SetInitialScale(sf::Vector2f vec)
	{ initialScale = UniformDistributionf(vec.x, vec.y); }

	void SetInitialScale(float val)
	{ initialScale = UniformDistributionf(val, val); }

	void SetInitialRotation(sf::Vector2f vec)
	{ initialScale = UniformDistributionf(vec.x, vec.y); }

	void SetInitialRotation(float val)
	{ initialScale = UniformDistributionf(val, val); }

	void SetRotationVelocity(sf::Vector2f vec)
	{ rotationVelocity = UniformDistributionf(vec.x, vec.y); }

	void SetRotationVelocity(float val)
	{ rotationVelocity = UniformDistributionf(val, val); }

	void SetEmissionRate(float rate)
	{
		if (rate <= 0.f)
		{
			emissionRate = 0.f;
		}
		else
		{
			emissionRate = 1/rate;
		}
	}
	
	void AddParticles(int num);
};
#endif