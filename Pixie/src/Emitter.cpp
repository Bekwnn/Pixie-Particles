#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Emitter.h"
#include "ParticleSystem.h"

Emitter::Emitter(sf::Texture &tex, float rate)
	: texture(&tex)
{
	maxParticles = 10000;	//default
	emissionCooldown = 0;
	numParticlesAlive = 0;
	SetSpawnLocation(sf::Vector2f(0.f, 0.f));
	SetInitialRotation(0);
	SetRotationVelocity(0);
	SetInitialScale(1.f);
	SetEmissionRate(rate);
}

void Emitter::Update(sf::RenderWindow &window, float deltaTime)
{
	//printf("EmitterUpdate:\n");
	for (std::list<Particle>::iterator i = particles.begin(); i != particles.end(); i++)
	{
		i->Update(window, deltaTime);
		if (i->life <= 0.f)
		{
			//printf("(Kill Particle!)");
			i = particles.erase(i); //erase particle if its life is over
			numParticlesAlive--;
		}
	}
	while (emissionCooldown <= 0.f && numParticlesAlive < maxParticles)
	{
		//printf("\nNewParticle\n");
		emissionCooldown += emissionRate;
		AddParticles(1);
	}
	emissionCooldown -= 1 * deltaTime;
	//printf("Cooldown %f\n", emissionCooldown);
	//Sleep(10);
}

void Emitter::Burst()
{
	if (bCanBurst) AddParticles(burstAmount);
}

void Emitter::AddParticles(int num)
{	
	for (int i = 0; i < num; i++)
	{
		if (numParticlesAlive > maxParticles) return;	//can't spawn any more
		
		particles.push_back(Particle(*this, *texture));
		numParticlesAlive++;
	}
}