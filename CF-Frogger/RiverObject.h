#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"

namespace GEX
{
	class TextNode;

	class Ally : public Entity
	{
	public:
		enum class  Type {
			wCatDown,
			wCatLeft,
			wCatRight,
			wCatUp,
			frogDown,
			frogLeft,
			frogRight,
			frogUp,
			bunnyDown,
			bunnyLeft,
			bunnyRight,
			bunnyUp,
			chickDown,
			chickLeft,
			chickRight,
			chickUp,
			seagullDown,
			seagullLeft,
			seagullRight,
			seagullUp
		};

	public:
		Ally(Type type = Type::frogUp);
		//Enemy(Enemy type, const TextureHolder& textures);

		virtual					~Ally() {};

		unsigned int			getCategory() const override;

		sf::FloatRect			getBoundingRect() const override;

		bool					isMarkedForRemoval() const;

		void					setType(Ally::Type type);
		void					setDirection(Ally::Type type);
		void					setSource(sf::Vector2i s);

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					movementUpdate(sf::Time dt);

	private:

		Type					_type;
		sf::Sprite				_sprite;

		sf::Vector2i			_source;

		sf::Clock				_walkSpeed;
		sf::Clock				_directionTimer;

		bool					_isMarkedForRemoval;
	};

}