#include "aircraft.hxx"

using airwar::Aircraft;
using airwar::AircraftType;

Aircraft::Aircraft(AircraftType type)
: type_(type) {}

void Aircraft::draw_current(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}