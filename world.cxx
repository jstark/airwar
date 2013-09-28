#include "world.hxx"
#include "aircraft.hxx"
#include <cmath>

using airwar::World;
using airwar::CommandQueue;

static const float MAX_WORLD_Y = 2000.f;

World::World(sf::RenderWindow &win)
: 
window(win),
world_view(window.getDefaultView()),
world_bounds(0.f, 0.f, world_view.getSize().x, MAX_WORLD_Y),
spawn_position(world_view.getSize().x / 2.0f, world_bounds.height - world_view.getSize().y),
scroll_speed(-50.0f),
player(nullptr)
{
	load_textures();
	build_scene();

	world_view.setCenter(spawn_position);
}

void World::load_textures()
{
	textures.load(textures::ID::Eagle,  "Media/Textures/Eagle.png");
	textures.load(textures::ID::Raptor, "Media/Textures/Raptor.png");
	textures.load(textures::ID::Desert, "Media/Textures/Desert.png");
}

void World::build_scene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		scene_layers[i] = layer.get();
		scene_graph.attach(std::move(layer));
	}

	// configure desert tile to be repeated
	sf::Texture &desert = textures.get(textures::ID::Desert);
	sf::IntRect rect(world_bounds);
	desert.setRepeated(true);

	std::unique_ptr<SpriteNode> background(new SpriteNode(desert, rect));
	background->setPosition(world_bounds.left, world_bounds.top); // 0.0, 0.0
	scene_layers[Background]->attach(std::move(background));

	// add the planes
	std::unique_ptr<Aircraft> leader(new Aircraft(AircraftType::Eagle, textures));
	player = leader.get();
	player->setPosition(spawn_position);
	player->set_velocity(40.0f, scroll_speed);
	scene_layers[Air]->attach(std::move(leader));

	// escort
	std::unique_ptr<Aircraft> left(new Aircraft(AircraftType::Raptor, textures));
	left->setPosition(-80.0f, 50.f);
	player->attach(std::move(left));

	std::unique_ptr<Aircraft> right(new Aircraft(AircraftType::Raptor, textures));
	right->setPosition(+80.0f, 50.f);
	player->attach(std::move(right));

}

void World::draw()
{
	window.setView(world_view);
	window.draw(scene_graph);
}

CommandQueue& World::get_command_queue()
{
	return command_queue;
}

void World::update(sf::Time dt)
{
	// we set velocity to 0, so that the player falls behind
	// as the view moves.
	world_view.move(0.0f, scroll_speed * dt.asSeconds());
	player->set_velocity(0.0f, 0.0f);

	// if a player has pressed an arrow key, then an appropriate
	// command will be inside command_queue, which when applied
	// on the scene graph, will increase the player's speed
	while (!command_queue.is_empty())
	{
		scene_graph.on_command(command_queue.pop(), dt);
	}

	// fix diagonal movement
	sf::Vector2f velocity = player->velocity();
	if (!velocity.x != 0.0f && velocity.y != 0.0f)
	{
		player->set_velocity(velocity / std::sqrt(2.0f));
	}

	// add scroll speed
	player->accelerate(0.0f, scroll_speed);
	scene_graph.update(dt);

	// apply bounds
	sf::FloatRect view_bounds(world_view.getCenter() - world_view.getSize() / 2.0f, world_view.getSize());
	const float border_distance = 40.0f;

	sf::Vector2f position = player->getPosition();
	position.x = std::max(position.x, view_bounds.left + border_distance);
	position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	position.y = std::max(position.y, view_bounds.top + border_distance);
	position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
	player->setPosition(position);
}
