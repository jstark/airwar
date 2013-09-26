#include "player.hxx"
#include "command.hxx"
#include "command_queue.hxx"
#include "category.hxx"
#include "scene.hxx"
#include "aircraft.hxx"
#include "SFML/System.hpp"
#include "SFML/Window/Event.hpp"
#include <iostream>

using airwar::Player;
using airwar::Command;
using airwar::CommandQueue;
using airwar::Category;
using airwar::SceneNode;
using airwar::Aircraft;

namespace
{
	template<typename GameObject, typename Function>
	std::function < void(SceneNode&, sf::Time > derived_action(Function fn)
	{
		return [=](SceneNode& node, sf::Time dt)
		{
			fn(static_cast<GameObject&>(node), dt);
		}
	}

	struct MoveAircraft
	{
		MoveAircraft(float vx, float vy)
			: velocity(vx, vy) {}

		void operator()(Aircraft& node, sf::Time dt) const
		{
			sf::Vector2f cvel = node.velocity();
			node.set_velocity(cvel + velocity);
		}

		sf::Vector2f velocity;
	};
}

// an example of a one-time command, we output the position of the player
// when he presses 'P'
void Player::handle_event(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = static_cast<unsigned int>(Category::PlayerAircraft);
		output.action = [](SceneNode& s, sf::Time dt)
		{
			std::cout << s.getPosition().x << ", " << s.getPosition().y << "\n";
		};
		commands.push(output);
	}
}

void Player::handle_realtime_input(CommandQueue& commands)
{
	const float player_speed{ 30.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Command move_left;
		move_left.category = static_cast<unsigned int>(Category::PlayerAircraft);
		move_left.action = derived_action<Aircraft>(MoveAircraft(-player_speed, 0.f));
		commands.push(move_left);
	}
}