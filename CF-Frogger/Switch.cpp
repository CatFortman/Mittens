#include "Switch.h"
#include "DataTables.h"

namespace GEX
{
	const std::map<Switch::Type, SwitchData> table = initializeSwitchData();

	sf::Vector2i switchSource(3, 0);

	TextureID toTextureID(Switch::Type type)
	{
		return TextureID::Switch;
	}

	Switch::Switch(Switch::Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_spinSpeed(),
		_hitpoints(table.at(type).hitPoints),
		_isMarkedForRemoval(false)
	{
	}


	Switch::~Switch()
	{
	}


	unsigned int Switch::getCategory() const
	{
		return Category::switchSprite;
	}

	sf::FloatRect Switch::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	bool Switch::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	Switch::Type Switch::getType() const
	{
		return _type;
	}

	void Switch::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		// check if Switch is still active

		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);
	}

	void Switch::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Switch::movementUpdate(sf::Time dt)
	{
		setType(_type);
		_sprite.setTextureRect(sf::IntRect(switchSource.x * 32, switchSource.y * 32, 32, 32));
	}

	void Switch::setType(Switch::Type type)
	{
		switch (type) {
		case Type::BlueForward:
		case Type::BlueLeft:
		case Type::BlueRight:
		case Type::BlueSide:
			switchSource.x = 3;
			break;
		case Type::GreenForward:
		case Type::GreenLeft:
		case Type::GreenRight:
		case Type::GreenSide:
			switchSource.x = 4;
			break;
		default:
			switchSource.x = 5;
			break;
		}

		sf::Time time;
		time = _spinSpeed.getElapsedTime();
		if (time.asMilliseconds() >= 300)
		{
			switchSource.y++;
			if (switchSource.y * 32 >= 128)
			{
				switchSource.y = 0;
			}
			_spinSpeed.restart();
		}
	}
}