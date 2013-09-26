#include "aircraft.hxx"
#include <stdexcept>

using airwar::Aircraft;
using airwar::AircraftType;

namespace
{
	using namespace airwar;

	textures::ID to_texture_id(AircraftType type)
	{
		switch (type)
		{
		case AircraftType::Eagle:
			return textures::ID::Eagle;
		case AircraftType::Raptor:
			return textures::ID::Raptor;
		default:
			throw new std::runtime_error("bad aircraft type !");
		}
	}
}

Aircraft::Aircraft(AircraftType type, const TextureHolder& textures)
: type_(type), sprite_(textures.get(to_texture_id(type))) 
{
	sf::FloatRect bounds = sprite_.getLocalBounds();
	sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::draw_current(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

unsigned int Aircraft::get_category() const
{
	if (type_ == AircraftType::Eagle)
	{
		return static_cast<unsigned int>(Category::PlayerAircraft);
	}
	else
	{
		return static_cast<unsigned int>(Category::EnemyAircraft);
	}
}