#include "entity.hxx"

using airwar::Entity;

void Entity::set_velocity(sf::Vector2f v)
{
	velocity_ = v;
}

void Entity::set_velocity(float vx, float vy)
{
	velocity_.x = vx;
	velocity_.y = vy;
}

sf::Vector2f Entity::velocity() const
{
	return velocity_;
}