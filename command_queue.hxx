#ifndef AIRWAR_COMMAND_QUEUE_HXX_INCLUDED
#define AIRWAR_COMMAND_QUEUE_HXX_INCLUDED

#include <queue>
#include "command.hxx"

namespace airwar
{
	class CommandQueue
	{
	public:
		void push(const Command& command);
		Command pop();
		bool is_empty() const;

	private:
		std::queue<Command> queue_;
	};
}

#endif // AIRWAR_COMMAND_QUEUE_HXX_INCLUDED