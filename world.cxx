#include "world.hxx"
#include "aircraft.hxx"

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
	world_view.move(0.0f, scroll_speed * dt.asSeconds());

	sf::Vector2f position = player->getPosition();
	sf::Vector2f velocity = player->velocity();

	if (position.x <= world_bounds.left + 150
		|| position.x >= world_bounds.left + world_bounds.width - 150)
	{
		velocity.x = -velocity.x;
		player->set_velocity(velocity);
	}
	scene_graph.update(dt);
}