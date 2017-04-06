#include "RiverObject.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX
{
	const std::map<Ally::Type, AllyData> table = initializeAllyData();

	TextureID toTextureID(Ally::Type type)
	{
		return TextureID::Animals;
	}

	Ally::Ally(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_isMarkedForRemoval(false),
		_walkSpeed(),
		_directionTimer(),
		_source(table.at(type).source)
	{
		// set up the animation
		centerOrigin(_sprite);

		// TextureHolder::getInstance().load(TextureID::animal, "../media/Textures/animalscrbetween.png");
		sf::FloatRect bounds = _sprite.getLocalBounds();
		_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	unsigned int Ally::getCategory() const
	{
		return Category::ally;
	}

	sf::FloatRect Ally::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Ally::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Ally::movementUpdate(sf::Time dt)
	{
		const std::vector<Direction>& directions = table.at(_type).directions;
		if (!directions.empty())
		{
			// set the type
			setType(_type);
			setDirection(_type);

			// set texture
			_sprite.setTextureRect(sf::IntRect(_source.x * 32, _source.y * 32, 32, 32));

			// set ai velocity
			switch (_type) {
			case Type::frogUp:
			case Type::bunnyUp:
			case Type::chickUp:
			case Type::seagullUp:
				setVelocity(0, -(table.at(_type).speed));
				break;
			case Type::frogDown:
			case Type::bunnyDown:
			case Type::chickDown:
			case Type::seagullDown:
				setVelocity(0, (table.at(_type).speed));
				break;
			case Type::frogLeft:
			case Type::bunnyLeft:
			case Type::chickLeft:
			case Type::seagullLeft:
				setVelocity(-(table.at(_type).speed), 0);
				break;
			default:
				setVelocity((table.at(_type).speed), 0);
				break;
			}
		}
	}

	void Ally::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		if (isDestroyed())
		{
			return;
		}

		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);
	}

	void Ally::setType(Ally::Type type)
	{
		_type = type;

		// change fram after 300 milliseconds
		sf::Time walkTime;
		walkTime = _walkSpeed.getElapsedTime();
		if (walkTime.asMilliseconds() >= 300)
		{
			_source.x++;
			if (_source.x * 32 >= table.at(_type).endOfFrame)
			{
				_source.x = table.at(_type).source.x;

			}
			_walkSpeed.restart();
		}

		_source.y = table.at(_type).source.y;

		/*switch (_type) {
		case Type::frogUp:
		case Type::bunnyUp:
		case Type::chickUp:
		case Type::seagullUp:
			allySource.y = 3;
			break;
		case Type::frogDown:
		case Type::bunnyDown:
		case Type::chickDown:
		case Type::seagullDown:
			allySource.y = 0;
			break;
		case Type::frogLeft:
		case Type::bunnyLeft:
		case Type::chickLeft:
		case Type::seagullLeft:
			allySource.y = 1;
			break;
		default:
			allySource.y = 2;
			break;
		}*/
	}

	void Ally::setDirection(Ally::Type type)
	{
		_type = type;

		// change type of animal thus direction
		sf::Time time;
		time = _directionTimer.getElapsedTime();
		if (time.asMilliseconds() >= 900)
		{
			// set ai direction
			switch (_type) {
			case Type::frogUp:
				_type = Type::frogRight;
				_directionTimer.restart();
				break;
			case Type::bunnyUp:
				_type = Type::bunnyRight;
				_directionTimer.restart();
				break;
			case Type::chickUp:
				_type = Type::chickRight;
				_directionTimer.restart();
				break;
			case Type::seagullUp:
				_type = Type::seagullRight;
				_directionTimer.restart();
				break;
			case Type::frogDown:
				_type = Type::frogLeft;
				_directionTimer.restart();
				break;
			case Type::bunnyDown:
				_type = Type::bunnyLeft;
				_directionTimer.restart();
				break;
			case Type::chickDown:
				_type = Type::chickLeft;
				_directionTimer.restart();
				break;
			case Type::seagullDown:
				_type = Type::seagullLeft;
				_directionTimer.restart();
				break;
			case Type::frogLeft:
				_type = Type::frogUp;
				_directionTimer.restart();
				break;
			case Type::bunnyLeft:
				_type = Type::bunnyUp;
				_directionTimer.restart();
				break;
			case Type::chickLeft:
				_type = Type::chickUp;
				_directionTimer.restart();
				break;
			case Type::seagullLeft:
				_type = Type::seagullUp;
				_directionTimer.restart();
				break;
			case Type::frogRight:
				_type = Type::frogDown;
				_directionTimer.restart();
				break;
			case Type::bunnyRight:
				_type = Type::bunnyDown;
				_directionTimer.restart();
				break;
			case Type::chickRight:
				_type = Type::chickDown;
				_directionTimer.restart();
				break;
			default:
				_type = Type::seagullDown;
				_directionTimer.restart();
				break;
			}
		}
	}

	void Ally::setSource(sf::Vector2i s)
	{
		_source = s;
	}

	bool Ally::isMarkedForRemoval() const
	{
		return isDestroyed();
	}
}