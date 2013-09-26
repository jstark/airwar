#ifndef AIRWAR_SCENE_HXX_INCLUDED
#define AIRWAR_SCENE_HXX_INCLUDED

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"

#include "category.hxx"

namespace airwar
{
	struct Command;

	class SceneNode : public sf::Drawable, public sf::Transformable
	{
	public:
		SceneNode() = default;
		SceneNode(const SceneNode&) = delete;

		using Ptr = std::unique_ptr<SceneNode>;

		void attach(Ptr node);
		Ptr detach(const SceneNode& node);

		void update(sf::Time dt);

		sf::Transform get_world_transform() const;
		sf::Vector2f get_world_position() const;

		virtual unsigned int get_category() const;

		void on_command(const Command& command, sf::Time dt);

	private:
		// drawable interface
		void draw(sf::RenderTarget &target, sf::RenderStates states) const final;

		// helper function, draws only the current object
		virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states) const;

		virtual void update_current(sf::Time dt);
		void update_children(sf::Time dt);

		std::vector<Ptr> children_;
		SceneNode *parent_{ nullptr };
	};

	class SpriteNode : public SceneNode
	{
	public:
		explicit SpriteNode(const sf::Texture& texture);
		SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

	private:
		void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
		sf::Sprite sprite_;
	};
}

#endif // AIRWAR_SCENE_HXX_INCLUDED