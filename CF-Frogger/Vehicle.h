#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"

namespace GEX
{
	class TextNode;

	class Enemy : public Entity
	{
	public:
		enum class  Type { wBirdDown, 
						   wBirdLeft, 
						   wBirdRight, 
						   wBirdUp, 
						   mouseDown, 
						   mouseLeft, 
						   mouseRight, 
						   mouseUp, 
						   roosterDown, 
						   roosterLeft, 
						   roosterRight, 
						   roosterUp,
						   raccoonDown,
						   raccoonLeft,
						   raccoonRight,
						   raccoonUp};

	public:
		Enemy(Type type = Type::raccoonUp);
		//Enemy(Enemy type, const TextureHolder& textures);

		virtual					~Enemy() {};

		unsigned int			getCategory() const override;

		sf::FloatRect			getBoundingRect() const override;

		bool					isMarkedForRemoval() const;

		void					setType(Enemy::Type type);
		void					setDirection(Enemy::Type type);

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					movementUpdate(sf::Time dt);

	private:

		Type					_type;
		sf::Sprite				_sprite;

		sf::Clock				_walkSpeed;
		sf::Clock				_directionTimer;
	
		bool					_isMarkedForRemoval;
	};

}
