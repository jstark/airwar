#ifndef AIRWAR_WORLD_HXX_INCLUDED
#define AIRWAR_WORLD_HXX_INCLUDED

#include "SFML/Graphics.hpp"
#include "texture_holder.hxx"
#include "command_queue.hxx"
#include "scene.hxx"
#include <array>

namespace airwar
{
	class Aircraft;

	class World final
	{
	public:
		explicit World(sf::RenderWindow &win);

		void update(sf::Time dt);

		enum Layer
		{
			Background,
			Air,
			LayerCount
		};

		void draw();

		CommandQueue& get_command_queue();

	private:
		void load_textures();
		void build_scene();
		/*
		 * A reference to the render window
		 */
		sf::RenderWindow &window;

		/*
		 * The world's view
		 */
		sf::View world_view;

		/*
		 * All game textures 
		 */
		TextureHolder textures;

		/*
		 * The root node of the scene graph
		 */
		SceneNode scene_graph;

		/*
		 * The children of the scene graph root node.
		 */
		std::array<SceneNode *, LayerCount> scene_layers;

		/*
		 * The world bounds
		 */
		sf::FloatRect world_bounds;

		/*
		 * The player's spawn position
		 */
		sf::Vector2f spawn_position;
		
		/*
		 * The player's scroll speed in Y axis
		 */
		float scroll_speed;

		/*
		 * A pointer to the player's aircraft
		 */
		Aircraft *player;

		/*
		 *
		 */
		CommandQueue command_queue;
	};
}

#endif // AIRWAR_WORLD_HXX_INCLUDED