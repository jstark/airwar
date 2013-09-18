#include "scene.hxx"
#include <utility>
#include <algorithm>
#include <cassert>

using airwar::SceneNode;
using airwar::SceneNode;

void SceneNode::attach(SceneNode::Ptr node)
{
	node->parent_ = this;
	children_.push_back(std::move(node));
}

SceneNode::Ptr SceneNode::detach(const SceneNode& node)
{
	auto found = std::find_if(children_.begin(), children_.end(),
		[&node](SceneNode::Ptr &p) -> bool { return p.get() == &node; });
	assert(found != children_.end());

	SceneNode::Ptr result = std::move(*found);
	result->parent_ = nullptr;
	children_.erase(found);
	return result; // move
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// TODO: check where the transform is set, I'm curious :)
	states.transform *= getTransform();

	// states now contains the absolute world transform
	// so we feed target, and states to `draw_current'
	// this will probably draw the sprite to an absolute position
	// in the world
	draw_current(target, states);
	for (const SceneNode::Ptr& node : children_) node->draw(target, states);
}


void SceneNode::draw_current(sf::RenderTarget &target, sf::RenderStates states) const
{
	// override to add functionality
}

void SceneNode::update(sf::Time dt)
{
	update_current(dt);
	update_children(dt);
}

void SceneNode::update_current(sf::Time dt)
{
	// override to add functionality
}

void SceneNode::update_children(sf::Time dt)
{
	for (auto& node : children_)
	{
		node->update(dt);
	}
}

sf::Transform SceneNode::get_world_transform() const
{
	sf::Transform tranform = sf::Transform::Identity;
	for (const SceneNode *node = this;
		node != nullptr; node = node->parent_)
	{
		tranform = node->getTransform() * tranform;
	}
	return tranform;
}

sf::Vector2f SceneNode::get_world_position() const
{
	return get_world_transform() * sf::Vector2f();
}