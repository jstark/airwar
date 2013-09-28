#ifndef AIRWAR_PLAYER_HXX_INCLUDED
#define AIRWAR_PLAYER_HXX_INCLUDED

#include "SFML/Window.hpp"
#include <map>

namespace airwar
{
	struct Command;
	class CommandQueue;

	enum class PlayerAction
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};

	class Player
	{
	public:
		Player();
		sf::Keyboard::Key assigned_key(PlayerAction action) const;
		void handle_event(const sf::Event &event, CommandQueue &commands);
		void handle_realtime_input(CommandQueue& commands);
	private:
		void initialize_actions();
		static bool is_realtime_action(PlayerAction action);

		std::map<sf::Keyboard::Key, PlayerAction> key_bindings;
		std::map<PlayerAction, Command> action_bindings;
	};
}

#endif // AIRWAR_PLAYER_HXX_INCLUDED