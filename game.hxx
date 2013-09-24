#ifndef AIRWAR_GAME_HXX_INCLUDED
#define AIRWAR_GAME_HXX_INCLUDED

#include "world.hxx"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace airwar
{
	class Game final {
	public:
		Game();

		void run();
	private:
		void process_events();
		void update(sf::Time elapsed_time);
		void render();
		void update_statistics(sf::Time elapsed_time);

		sf::RenderWindow window;
		World world;

		sf::Font font;
		sf::Text statistics_text;
		sf::Time statistics_update_time;
		std::size_t statistics_num_frames{ 0 };

		bool is_paused{ false };
	};
}

#endif // AIRWAR_GAME_HXX_INCLUDED