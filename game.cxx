#include "game.hxx"

using airwar::Game;

const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);

Game::Game()
:
window(sf::VideoMode(640, 480), "World", sf::Style::Close),
world(window)
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (window.isOpen())
	{
		sf::Time elapsed_time = clock.restart();
		time_since_last_update += elapsed_time;
		while (time_since_last_update > TimePerFrame)
		{
			time_since_last_update -= TimePerFrame;
			process_events();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::process_events()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			break;
		case sf::Event::KeyReleased:
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(sf::Time elapsed_time)
{
	world.update(elapsed_time);
}

void Game::render()
{
	window.clear();
	world.draw();
	window.display();
}