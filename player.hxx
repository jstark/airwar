#ifndef AIRWAR_PLAYER_HXX_INCLUDED
#define AIRWAR_PLAYER_HXX_INCLUDED

namespace sf
{
	class Event;
}

namespace airwar
{
	class CommandQueue;

	class Player
	{
	public:
		void handle_event(const sf::Event &event, CommandQueue &commands);
		void handle_realtime_input(CommandQueue& commands);
	};
}

#endif // AIRWAR_PLAYER_HXX_INCLUDED