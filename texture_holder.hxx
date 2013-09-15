#ifndef AIRWAR_TEXTURE_HOLDER_HXX_INCLUDED
#define AIRWAR_TEXTURE_HOLDER_HXX_INCLUDED

#include "resource_holder.hxx"

// forward declaration
namespace sf { class Texture;  }

namespace airwar
{
	namespace textures
	{
		enum class ID
		{
			Eagle,
			Raptor
		};
	}

	using TextureHolder = ResourceHolder<sf::Texture, textures::ID>;
}

#endif // AIRWAR_TEXTURE_HOLDER_HXX_INCLUDED