#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "ParticleSystem.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Pixie Particles");
	sf::Texture texture;
	sf::Clock fpsclock;

	texture.loadFromFile("particle.png");
	
	ParticleSystem partSys = ParticleSystem(window);
	Emitter emitter = Emitter(texture, 30.f);
	emitter.SetSpawnLocation(sf::Vector2f(50.f, 40.f), sf::Vector2f(750.f, 160.f));
	emitter.SetSpawnVelocity(sf::Vector2f(-20.f, -20.f), sf::Vector2f(20.f, 20.f));
	emitter.SetInitialScale(sf::Vector2f(0.2f, 2.f));
	emitter.SetRotationVelocity(sf::Vector2f(0.f, 90.f));
	emitter.lifetime = 7.f;
	emitter.acceleration = sf::Vector2f(0.f, 40.f);
	emitter.bCanBurst = true;
	emitter.burstAmount = 200;
	partSys.AddEmitter(emitter);
	
	Emitter splosion = Emitter(texture, 0.05f);
	splosion.SetSpawnLocation(sf::Vector2f(600.f, 400.f), sf::Vector2f(600.f, 400.f));
	splosion.SetSpawnVelocity(sf::Vector2f(-60.f, -60.f), sf::Vector2f(60.f, 60.f));
	splosion.lifetime = 3.f;
	splosion.color = sf::Color::Red;
	splosion.bCanBurst = true;
	splosion.burstAmount = 200;
	//partSys.AddEmitter(splosion);
	
	Emitter blue = Emitter(texture, 100.f);
	blue.SetSpawnLocation(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
	blue.SetSpawnVelocity(sf::Vector2f(0.f, 0.f), sf::Vector2f(20.f, 20.f));
	blue.lifetime = 15.f;
	blue.color = sf::Color::Blue;
	blue.bCanBurst = true;
	blue.burstAmount = 100;
	//partSys.AddEmitter(blue);
	
	bool lmbheld = false;
	bool rmbheld = false;
	float deltaTime;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time time = fpsclock.getElapsedTime();
		deltaTime = time.asSeconds();
		fpsclock.restart().asSeconds();

		window.clear();

		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (!lmbheld)
			{
				blue.Burst();
			}
			lmbheld = true;
		}
		else lmbheld = false;

		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			if (!rmbheld)
			{
				emitter.Burst();
				splosion.Burst();
			}
			rmbheld = true;
		}
		else rmbheld = false;

		partSys.Update(deltaTime);
		window.display();
	}

	return 0;
}