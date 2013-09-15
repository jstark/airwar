#ifndef AIRWAR_AIRCRAFT_HXX_INCLUDED
#define AIRWAR_AIRCRAFT_HXX_INCLUDED

#include "entity.hxx"
#include "texture_holder.hxx"
#include "SFML/Graphics.hpp"

namespace airwar
{
	enum class AircraftType
	{
		Eagle,
		Raptor
	};

	class Aircraft : public Entity
	{
	public:
		explicit Aircraft(AircraftType type, const TextureHolder &textures);

		// sf::Drawable interface
		void draw_current(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		AircraftType type_;
		sf::Sprite sprite_;
	};
}

#endif // AIRWAR_AIRCRAFT_HXX_INCLUDED