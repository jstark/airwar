#include "command_queue.hxx"

using airwar::CommandQueue;
using airwar::Command;

void CommandQueue::push(const Command& command)
{
	queue_.push(command);
}

Command CommandQueue::pop()
{
	Command command = queue_.front();
	queue_.pop();
	return command;
}

bool CommandQueue::is_empty() const
{
	return queue_.empty();
}