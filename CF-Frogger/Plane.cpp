
#include "Plane.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX
{
	const std::map<Cat::Type, CatData> table = initializeCatData();

	sf::Vector2i source(2, 0);

	TextureID toTextureID(Cat::Type type)
	{
		return TextureID::Cats;
	}

	Cat::Cat(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_dying(false),
		_points(0),
		_deathTimer(),
		_walkSpeed(),
		_isMarkedForRemoval(false)
	{
		// set up the animation
		centerOrigin(_sprite);

		// TextureHolder::getInstance().load(TextureID::AIRCat, "../media/Textures/Idles.png");
		sf::FloatRect bounds = _sprite.getLocalBounds();
		_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

		std::unique_ptr<TextNode> healthDisplay(new TextNode(std::to_string(getHitPoints()) + "HP"));
		_healthDisplay = healthDisplay.get();
		healthDisplay->setPosition(0.f, 50.f);
		attatchChild(std::move(healthDisplay));
	}

	unsigned int Cat::getCategory() const
	{
		return Category::playerCharacter;
	}

	sf::FloatRect Cat::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Cat::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Cat::movementUpdate(sf::Time dt)
	{
		_sprite.setTextureRect(sf::IntRect(source.x * 48, source.y * 48, 48, 48));
	}

	void Cat::adjustCatLives()
	{
		//_CatLife1->isMarkedForRemoval();
		//		_CatLife1->destroy();
	}

	void Cat::playDeathAnimation()
	{
		setIsDying(false);
		setIsRespawning(true);
	}

	void Cat::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// check if Catger died

		if (!isDying() && !isRespawing())
		{
			movementUpdate(dt);
			Entity::updateCurrent(dt, commands);
		}
		else
		{
			playDeathAnimation();
		}
		updateTexts();
	}

	void Cat::updateTexts()
	{
		/*_healthDisplay->setText(std::to_string(getHitPoints()) + "HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());*/
	}

	bool Cat::isMarkedForRemoval() const
	{
		return isDestroyed();
	}


	void Cat::setIsDying(bool dying)
	{
		_dying = dying;
	}

	bool Cat::isDying()
	{
		return _dying;
	}

	void Cat::setIsRespawning(bool respawning)
	{
		_respawning = respawning;
	}

	bool Cat::isRespawing()
	{
		return _respawning;
	}

	void Cat::setType(Cat::Type type)
	{
		_type = type;

		sf::Time time;
		time = _walkSpeed.getElapsedTime();
		if (time.asMilliseconds() >= 200)
		{
			source.x++;
			if (source.x * 48 >= 144)
			{
				source.x = 0;
			}
			_walkSpeed.restart();
		}

		switch (_type) {
		case Type::Up:
			source.y = 3;
			break;
		case Type::Down:
			source.y = 0;
			break;
		case Type::Left:
			source.y = 1;
			break;
		default: 
			source.y = 2;
			break;
		}
	}

	Cat::Type Cat::getType() const
	{
		return _type;
	}
}