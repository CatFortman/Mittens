#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "SFML/Graphics.hpp"

namespace GEX
{
	class Switch : public Entity
	{
	public:

		enum class  Type { BlueLeft, BlueForward, BlueRight, BlueSide, RedLeft, RedForward, RedRight, RedSide, GreenLeft, GreenForward, GreenRight, GreenSide	};
	
	public:

		Switch(Type type = Type::BlueLeft);
		~Switch();

		unsigned int			getCategory() const;

		sf::FloatRect			getBoundingRect() const override;

		bool					isMarkedForRemoval() const;

		void					setType(Switch::Type type);
		Switch::Type			getType() const;

		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					movementUpdate(sf::Time dt);

	private:

		Type					_type;
		sf::Sprite				_sprite;
		int						_hitpoints;

		sf::Clock				_spinSpeed;
		bool					_isMarkedForRemoval;
	};
}
