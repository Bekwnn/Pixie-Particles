#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(sf::RenderWindow &win)
	: window(&win)
{
	//TODO: create default bounding box (using win coordinates?)
}

ParticleSystem::ParticleSystem(sf::RenderWindow &win, sf::Rect<int> bounds)
	: window(&win), boundingBox(bounds)
{
	
}

void ParticleSystem::AddEmitter(Emitter &emitter)
{
	emitter.SetParticleSystem(this);
	emitters.push_back(&emitter);
}

void ParticleSystem::Update(float deltaTime)
{
	//TODO: bounding box check
	for (Emitter* emitter : emitters)
	{
		emitter->Update(*window, deltaTime);
	}
}

//calls Burst() on all emitters that can burst
void ParticleSystem::Burst()
{
	for (Emitter* emitter : emitters)
	{
		emitter->Burst();
	}
}