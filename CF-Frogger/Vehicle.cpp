#include "Vehicle.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"
#include "Utility.h"
#include "DataTables.h"

#include <cassert>
namespace GEX
{
	const std::map<Enemy::Type, EnemyData> table = initializeEnemyData();


	TextureID toTextureID(Enemy::Type type)
	{
		switch (type)
		{
		case Enemy::Type::raccoonDown:
		case Enemy::Type::raccoonLeft:
		case Enemy::Type::raccoonRight:
		case Enemy::Type::raccoonUp:
			return TextureID::Raccoon;
			break;
		default:
			return TextureID::Animals;
			break;
		}
	}

	Enemy::Enemy(Type type) :
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

	unsigned int Enemy::getCategory() const
	{
		return Category::enemy;
	}

	sf::FloatRect Enemy::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Enemy::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Enemy::movementUpdate(sf::Time dt)
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
			case Type::wBirdUp:
			case Type::mouseUp:
			case Type::roosterUp:
			case Type::raccoonUp:
				setVelocity(0,-(table.at(_type).speed));
				break;
			case Type::wBirdDown:
			case Type::mouseDown:
			case Type::roosterDown:
			case Type::raccoonDown:
				setVelocity(0, (table.at(_type).speed));
				break;
			case Type::wBirdLeft:
			case Type::mouseLeft:
			case Type::roosterLeft:
			case Type::raccoonLeft:
				setVelocity(-(table.at(_type).speed), 0);
				break;
			default:
				setVelocity((table.at(_type).speed), 0);
				break;
			}			
		}
	}

	void Enemy::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		if (isDestroyed())
		{
			return;
		}

		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);
	}

	void Enemy::setType(Enemy::Type type)
	{
		_type = type;

		// change fram after 300 milliseconds
		sf::Time walkTime;
		walkTime = _walkSpeed.getElapsedTime();
		if (walkTime.asMilliseconds() >= 300)
		{
			_source.x++;
			if (_source.x * 32 >= 96)
			{
				_source.x = 0;
			}
			_walkSpeed.restart();
		}


		switch (_type) {
		case Type::wBirdUp:
		case Type::mouseUp:
		case Type::roosterUp:
		case Type::raccoonUp:
			_source.y = 3;
			break;
		case Type::wBirdDown:
		case Type::mouseDown:
		case Type::roosterDown:
		case Type::raccoonDown:
			_source.y = 0;
			break;
		case Type::wBirdLeft:
		case Type::mouseLeft:
		case Type::roosterLeft:
		case Type::raccoonLeft:
			_source.y = 1;
			break;
		default:
			_source.y = 2;
			break;
		}
	}

	void Enemy::setDirection(Enemy::Type type)
	{
		_type = type;

		// change type of animal thus direction
		sf::Time time;
		time = _directionTimer.getElapsedTime();
		if (time.asMilliseconds() >= 900)
		{
			// set ai direction
			switch (_type) {
			case Type::wBirdUp:
				_type = Type::wBirdRight;
				_directionTimer.restart();
				break;
			case Type::mouseUp:
				_type = Type::mouseRight;
				_directionTimer.restart();
				break;
			case Type::roosterUp:
				_type = Type::roosterRight;
				_directionTimer.restart();
				break;
			case Type::raccoonUp:
				_type = Type::raccoonRight;
				_directionTimer.restart();
				break;
			case Type::wBirdDown:
				_type = Type::wBirdLeft;
				_directionTimer.restart();
				break;
			case Type::mouseDown:
				_type = Type::mouseLeft;
				_directionTimer.restart();
				break;
			case Type::roosterDown:
				_type = Type::roosterLeft;
				_directionTimer.restart();
				break;
			case Type::raccoonDown:
				_type = Type::raccoonLeft;
				_directionTimer.restart();
				break;
			case Type::wBirdLeft:
				_type = Type::wBirdUp;
				_directionTimer.restart();
				break;
			case Type::mouseLeft:
				_type = Type::mouseUp;
				_directionTimer.restart();
				break;
			case Type::roosterLeft:
				_type = Type::roosterUp;
				_directionTimer.restart();
				break;
			case Type::raccoonLeft:
				_type = Type::raccoonUp;
				_directionTimer.restart();
				break;
			case Type::wBirdRight:
				_type = Type::wBirdDown;
				_directionTimer.restart();
				break;
			case Type::mouseRight:
				_type = Type::mouseDown;
				_directionTimer.restart();
				break;
			case Type::roosterRight:
				_type = Type::roosterDown;
				_directionTimer.restart();
				break;
			default:
				_type = Type::raccoonDown;
				_directionTimer.restart();
				break;
			}
		}
	}

	void Enemy::setSource(sf::Vector2i s)
	{
		_source = s;
	}

	bool Enemy::isMarkedForRemoval() const
	{
		return isDestroyed();
	}
}
