#ifndef AIRWAR_ENTITY_HXX_INCLUDED
#define AIRWAR_ENTITY_HXX_INCLUDED

#include "SFML/System.hpp"
#include "scene.hxx"

namespace airwar {

	/**
	 *	An entity is a game element in the world. It can be an airplane, a missile,
	 *	a pickup etc.
	 */
	class Entity : public SceneNode
	{
	public:
		void set_velocity(sf::Vector2f v);
		void set_velocity(float vx, float vy);
		void accelerate(sf::Vector2f velocity);
		void accelerate(float vx, float vy);
		sf::Vector2f velocity() const;
	private:
		void update_current(sf::Time dt) override;

		sf::Vector2f velocity_{ 0.f, 0.f };
	};
}

#endif // AIRWAR_ENTITY_HXX_INCLUDED