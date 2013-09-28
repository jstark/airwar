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
using airwar::PlayerAction;

namespace
{
	template<typename GameObject, typename Function>
	std::function < void(SceneNode&, sf::Time) > derived_action(Function fn)
	{
		return [=](SceneNode& node, sf::Time dt)
		{
			fn(static_cast<GameObject&>(node), dt);
		};
	}

	struct MoveAircraft
	{
		MoveAircraft(float vx, float vy)
			: velocity(vx, vy) {}

		void operator()(Aircraft& node, sf::Time dt) const
		{
			node.accelerate(velocity);
		}

		sf::Vector2f velocity;
	};
}

Player::Player()
{
	// default key bindings
	key_bindings[sf::Keyboard::Left] = PlayerAction::MoveLeft;
	key_bindings[sf::Keyboard::Right] = PlayerAction::MoveRight;
	key_bindings[sf::Keyboard::Up] = PlayerAction::MoveUp;
	key_bindings[sf::Keyboard::Down] = PlayerAction::MoveDown;

	// initial action bindings
	initialize_actions();

	// assign categories
	for (auto & p : action_bindings)
	{
		p.second.category = static_cast<unsigned int>(Category::PlayerAircraft);
	}
}

void Player::initialize_actions()
{
	const float player_speed = 200.f;
	action_bindings[PlayerAction::MoveLeft].action = derived_action<Aircraft>(MoveAircraft(-player_speed, 0.0f));
	action_bindings[PlayerAction::MoveRight].action = derived_action<Aircraft>(MoveAircraft(+player_speed, 0.0f));
	action_bindings[PlayerAction::MoveUp].action = derived_action<Aircraft>(MoveAircraft(0.0f, -player_speed));
	action_bindings[PlayerAction::MoveDown].action = derived_action<Aircraft>(MoveAircraft(0.0f, +player_speed));
}

// an example of a one-time command, we output the position of the player
// when he presses 'P'
void Player::handle_event(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = key_bindings.find(event.key.code);
		if (found != key_bindings.end() && !is_realtime_action(found->second))
		{
			commands.push(action_bindings[found->second]);
		}
	}
}

void Player::handle_realtime_input(CommandQueue& commands)
{
	for (const auto& p : key_bindings)
	{
		if (sf::Keyboard::isKeyPressed(p.first) && is_realtime_action(p.second))
		{
			commands.push(action_bindings[p.second]);
		}
	}
}

sf::Keyboard::Key Player::assigned_key(PlayerAction action) const
{
	for (const auto& p : key_bindings)
	{
		if (p.second == action)
		{
			return p.first;
		}
	}
	return sf::Keyboard::Unknown;
}

bool Player::is_realtime_action(PlayerAction action)
{
	switch (action)
	{
	case PlayerAction::MoveLeft:
	case PlayerAction::MoveRight:
	case PlayerAction::MoveDown:
	case PlayerAction::MoveUp:
		return true;
	default:
		return false;
	}
}
