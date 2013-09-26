#include "game.hxx"
#include <string>

using airwar::Game;

const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);

Game::Game()
:
window{ sf::VideoMode(640, 480), "World", sf::Style::Close },
world{ window }
{
	font.loadFromFile("Media/Sansation.ttf");
	statistics_text.setFont(font);
	statistics_text.setPosition(5.0f, 5.0f);
	statistics_text.setCharacterSize(10);
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
			if (!is_paused) update(TimePerFrame);
		}
		update_statistics(elapsed_time);
		render();
	}
}

void Game::process_events()
{
	CommandQueue& commands = world.get_command_queue();

	sf::Event event;
	while (window.pollEvent(event))
	{
		player.handle_event(event, commands);
		if (event.type == sf::Event::Closed)
		{
			window.close();
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

	// statistics
	window.setView(window.getDefaultView());
	window.draw(statistics_text);
	window.display();
}

void Game::update_statistics(sf::Time elapsed_time)
{
	statistics_update_time += elapsed_time;
	statistics_num_frames += 1;

	if (statistics_update_time >= sf::seconds(1.0f))
	{
		statistics_text.setString(
			"Frames / Second = " + std::to_string(statistics_num_frames) + "\n" +
			"Time / Update = " + std::to_string(statistics_update_time.asMicroseconds() / statistics_num_frames) + "us");
		statistics_update_time -= sf::seconds(1.0f);
		statistics_num_frames = 0;
	}
}