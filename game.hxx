#ifndef AIRWAR_GAME_HXX_INCLUDED
#define AIRWAR_GAME_HXX_INCLUDED

#include "world.hxx"
#include "SFML/System/Time.hpp"

#include "SFML/Graphics.hpp"

namespace airwar
{
	class Game final {
	public:
		Game();

		void run();
	private:
		void process_events();
		void update(sf::Time elapsedTime);
		void render();

		sf::RenderWindow window;
		World world;
	};
}

#endif // AIRWAR_GAME_HXX_INCLUDED