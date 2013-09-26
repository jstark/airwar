#ifndef AIRWAR_COMMAND_HXX_INCLUDED
#define AIRWAR_COMMAND_HXX_INCLUDED

#include <functional>
#include "category.hxx"

namespace sf
{
	class Time;
}

namespace airwar
{
	class SceneNode;

	struct Command
	{
		std::function<void(SceneNode&, sf::Time)> action;
		unsigned int category{ static_cast<unsigned int>(Category::None) };
	};
}

#endif // AIRWAR_COMMAND_HXX_INCLUDED