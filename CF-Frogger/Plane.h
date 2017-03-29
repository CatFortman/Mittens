#pragma once

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Animation.h"

namespace GEX 
{
	class TextNode;

	class Cat : public Entity
	{
	public:
		enum class  Type { Down, Left, Right, Up };
		
	public:
								Cat(Type type = Type::Up);
								//Cat(Cats type, const TextureHolder& textures);

		virtual					~Cat() {};

		unsigned int			getCategory() const override;

		sf::FloatRect			getBoundingRect() const override;

		bool					isMarkedForRemoval() const;
		void					adjustCatLives();
		void					setIsDying(bool dying);
		bool					isDying();

		void					setIsRespawning(bool dying);
		bool					isRespawing();

		void					playDeathAnimation();

		void					setType(Cat::Type type);
		Cat::Type				getType() const;

	private:
		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		void					updateCurrent(sf::Time dt, CommandQueue& commands);
		void					movementUpdate(sf::Time dt);
		void					updateTexts();

	private:

		TextNode*				_healthDisplay;
		Type					_type;
		sf::Sprite				_sprite;

		sf::Clock				_deathTimer;
		sf::Clock				_walkSpeed;

		bool				    _respawning;
		bool					_dying;

		bool					_isMarkedForRemoval;

		int						_points;
	};

}