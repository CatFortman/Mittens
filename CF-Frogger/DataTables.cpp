/**
@file
@author  Cat Fortman
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "DataTables.h"
#include "Plane.h"
#include "ParticleNode.h"
#include "Vehicle.h"
#include "RiverObject.h"

#include <functional>

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

namespace GEX
{
	Direction::Direction(Enemy::Type et) : eType(et)
	{}

	Direction::Direction(Ally::Type at) : aType(at)
	{}

	std::map<Cat::Type, CatData> initializeCatData()
	{
		std::map<Cat::Type, CatData> data;

		data[Cat::Type::Down].hitPoints = 100;
		data[Cat::Type::Down].texture = TextureID::Cats;
		data[Cat::Type::Down].textureRect = sf::IntRect(0, 0, 48, 48);

		data[Cat::Type::Up].hitPoints = 100;
		data[Cat::Type::Up].texture = TextureID::Cats;
		data[Cat::Type::Up].textureRect = sf::IntRect(144, 0, 48, 48);

		data[Cat::Type::Left].hitPoints = 0;
		data[Cat::Type::Left].texture = TextureID::Cats;
		data[Cat::Type::Left].textureRect = sf::IntRect(48, 0, 48, 48);

		data[Cat::Type::Right].hitPoints = 0;
		data[Cat::Type::Right].texture = TextureID::Cats;
		data[Cat::Type::Right].textureRect = sf::IntRect(96, 0, 48, 48);
		
		return data;
	}

	std::map<Particle::Type, ParticleData> initializeParticleData()
	{
		std::map<Particle::Type, ParticleData> data;

		data[Particle::Type::propellant].color = sf::Color(255, 255, 50);
		data[Particle::Type::propellant].lifetime = sf::seconds(0.6f);

		data[Particle::Type::smoke].color = sf::Color(50, 50, 50);
		data[Particle::Type::smoke].lifetime = sf::seconds(4.f);

		return data;
	}

	std::map<Switch::Type, SwitchData> initializeSwitchData()
	{
		std::map<Switch::Type, SwitchData>	data;

		// left, forward, right, side

		data[Switch::Type::BlueLeft].hitPoints = 100;
		data[Switch::Type::BlueLeft].texture = TextureID::Switch;
		data[Switch::Type::BlueLeft].textureRect = sf::IntRect(96, 0, 32, 32);

		data[Switch::Type::BlueForward].hitPoints = 100;
		data[Switch::Type::BlueForward].texture = TextureID::Switch;
		data[Switch::Type::BlueForward].textureRect = sf::IntRect(96, 32, 32, 32);

		data[Switch::Type::BlueRight].hitPoints = 100;
		data[Switch::Type::BlueRight].texture = TextureID::Switch;
		data[Switch::Type::BlueRight].textureRect = sf::IntRect(96, 64, 32, 32);

		data[Switch::Type::BlueSide].hitPoints = 100;
		data[Switch::Type::BlueSide].texture = TextureID::Switch;
		data[Switch::Type::BlueSide].textureRect = sf::IntRect(96, 96, 32, 32);

		data[Switch::Type::RedLeft].hitPoints = 100;
		data[Switch::Type::RedLeft].texture = TextureID::Switch;
		data[Switch::Type::RedLeft].textureRect = sf::IntRect(128, 0, 32, 32);

		data[Switch::Type::RedForward].hitPoints = 100;
		data[Switch::Type::RedForward].texture = TextureID::Switch;
		data[Switch::Type::RedForward].textureRect = sf::IntRect(128, 32, 32, 32);

		data[Switch::Type::RedRight].hitPoints = 100;
		data[Switch::Type::RedRight].texture = TextureID::Switch;
		data[Switch::Type::RedRight].textureRect = sf::IntRect(128, 64, 32, 32);

		data[Switch::Type::RedSide].hitPoints = 100;
		data[Switch::Type::RedSide].texture = TextureID::Switch;
		data[Switch::Type::RedSide].textureRect = sf::IntRect(128, 96, 32, 32);

		data[Switch::Type::GreenLeft].hitPoints = 100;
		data[Switch::Type::GreenLeft].texture = TextureID::Switch;
		data[Switch::Type::GreenLeft].textureRect = sf::IntRect(160, 0, 32, 32);

		data[Switch::Type::GreenForward].hitPoints = 100;
		data[Switch::Type::GreenForward].texture = TextureID::Switch;
		data[Switch::Type::GreenForward].textureRect = sf::IntRect(160, 32, 32, 32);

		data[Switch::Type::GreenRight].hitPoints = 100;
		data[Switch::Type::GreenRight].texture = TextureID::Switch;
		data[Switch::Type::GreenRight].textureRect = sf::IntRect(160, 64, 32, 32);

		data[Switch::Type::GreenSide].hitPoints = 100;
		data[Switch::Type::GreenSide].texture = TextureID::Switch;
		data[Switch::Type::GreenSide].textureRect = sf::IntRect(160, 96, 32, 32);

		return data;
	}

	std::map<Ally::Type, AllyData> initializeAllyData()
	{
		std::map<Ally::Type, AllyData> data;

		data[Ally::Type::wCatDown].texture = TextureID::Animals;
		data[Ally::Type::wCatDown].textureRect = sf::IntRect(0, 0, 32, 32);
		data[Ally::Type::wCatDown].speed = 90.f;
		data[Ally::Type::wCatDown].directions.push_back(Direction(Ally::Type::wCatDown));
		data[Ally::Type::wCatDown].source = sf::Vector2i(0, 0);
		data[Ally::Type::wCatDown].endOfFrame = 64;

		data[Ally::Type::wCatLeft].texture = TextureID::Animals;
		data[Ally::Type::wCatLeft].textureRect = sf::IntRect(32, 0, 32, 32);
		data[Ally::Type::wCatLeft].speed = 90.f;
		data[Ally::Type::wCatLeft].directions.push_back(Direction(Ally::Type::wCatLeft));
		data[Ally::Type::wCatLeft].source = sf::Vector2i(0, 1);
		data[Ally::Type::wCatLeft].endOfFrame = 64;

		data[Ally::Type::wCatRight].texture = TextureID::Animals;
		data[Ally::Type::wCatRight].textureRect = sf::IntRect(64, 0, 32, 32);
		data[Ally::Type::wCatRight].speed = 90.f;
		data[Ally::Type::wCatRight].directions.push_back(Direction(Ally::Type::wCatRight));
		data[Ally::Type::wCatRight].source = sf::Vector2i(0, 2);
		data[Ally::Type::wCatRight].endOfFrame = 64;

		data[Ally::Type::wCatUp].texture = TextureID::Animals;
		data[Ally::Type::wCatUp].textureRect = sf::IntRect(96, 0, 32, 32);
		data[Ally::Type::wCatUp].speed = 90.f;
		data[Ally::Type::wCatUp].directions.push_back(Direction(Ally::Type::wCatUp));
		data[Ally::Type::wCatUp].source = sf::Vector2i(0, 3);
		data[Ally::Type::wCatUp].endOfFrame = 64;

		data[Ally::Type::frogDown].texture = TextureID::Animals;
		data[Ally::Type::frogDown].textureRect = sf::IntRect(128, 192, 32, 32);
		data[Ally::Type::frogDown].speed = 90.f;
		data[Ally::Type::frogDown].directions.push_back(Direction(Ally::Type::frogDown));
		data[Ally::Type::frogDown].source = sf::Vector2i(6, 4);
		data[Ally::Type::frogDown].endOfFrame = 256;

		data[Ally::Type::frogLeft].texture = TextureID::Animals;
		data[Ally::Type::frogLeft].textureRect = sf::IntRect(160, 192, 32, 32);
		data[Ally::Type::frogLeft].speed = 90.f;
		data[Ally::Type::frogLeft].directions.push_back(Direction(Ally::Type::frogLeft));
		data[Ally::Type::frogLeft].source = sf::Vector2i(6, 5);
		data[Ally::Type::frogLeft].endOfFrame = 256;

		data[Ally::Type::frogRight].texture = TextureID::Animals;
		data[Ally::Type::frogRight].textureRect = sf::IntRect(192, 192, 32, 32);
		data[Ally::Type::frogRight].speed = 90.f;
		data[Ally::Type::frogRight].directions.push_back(Direction(Ally::Type::frogRight));
		data[Ally::Type::frogRight].source = sf::Vector2i(6, 6);
		data[Ally::Type::frogRight].endOfFrame = 256;

		data[Ally::Type::frogUp].texture = TextureID::Animals;
		data[Ally::Type::frogUp].textureRect = sf::IntRect(224, 192, 32, 32);
		data[Ally::Type::frogUp].speed = 90.f;
		data[Ally::Type::frogUp].directions.push_back(Direction(Ally::Type::frogUp));
		data[Ally::Type::frogUp].source = sf::Vector2i(6, 7);
		data[Ally::Type::frogUp].endOfFrame = 256;

		data[Ally::Type::bunnyDown].texture = TextureID::Animals;
		data[Ally::Type::bunnyDown].textureRect = sf::IntRect(128, 288, 32, 32);
		data[Ally::Type::bunnyDown].speed = 90.f;
		data[Ally::Type::bunnyDown].directions.push_back(Direction(Ally::Type::bunnyDown));
		data[Ally::Type::bunnyDown].source = sf::Vector2i(9, 4);
		data[Ally::Type::bunnyDown].endOfFrame = 352;

		data[Ally::Type::bunnyLeft].texture = TextureID::Animals;
		data[Ally::Type::bunnyLeft].textureRect = sf::IntRect(160, 288, 32, 32);
		data[Ally::Type::bunnyLeft].speed = 90.f;
		data[Ally::Type::bunnyLeft].directions.push_back(Direction(Ally::Type::bunnyLeft));
		data[Ally::Type::bunnyLeft].source = sf::Vector2i(9, 5);
		data[Ally::Type::bunnyLeft].endOfFrame = 352;

		data[Ally::Type::bunnyRight].texture = TextureID::Animals;
		data[Ally::Type::bunnyRight].textureRect = sf::IntRect(192, 288, 32, 32);
		data[Ally::Type::bunnyRight].speed = 90.f;
		data[Ally::Type::bunnyRight].directions.push_back(Direction(Ally::Type::bunnyRight));
		data[Ally::Type::bunnyRight].source = sf::Vector2i(9, 6);
		data[Ally::Type::bunnyRight].endOfFrame = 352;

		data[Ally::Type::bunnyUp].texture = TextureID::Animals;
		data[Ally::Type::bunnyUp].textureRect = sf::IntRect(224, 288, 32, 32);
		data[Ally::Type::bunnyUp].speed = 90.f;
		data[Ally::Type::bunnyUp].directions.push_back(Direction(Ally::Type::bunnyUp));
		data[Ally::Type::bunnyUp].source = sf::Vector2i(9, 7);
		data[Ally::Type::bunnyUp].endOfFrame = 352;

		data[Ally::Type::chickDown].texture = TextureID::Animals;
		data[Ally::Type::chickDown].textureRect = sf::IntRect(128, 0, 32, 32);
		data[Ally::Type::chickDown].speed = 90.f;
		data[Ally::Type::chickDown].directions.push_back(Direction(Ally::Type::chickRight));
		data[Ally::Type::chickDown].source = sf::Vector2i(0, 4);
		data[Ally::Type::chickDown].endOfFrame = 64;

		data[Ally::Type::chickLeft].texture = TextureID::Animals;
		data[Ally::Type::chickLeft].textureRect = sf::IntRect(160, 0, 32, 32);
		data[Ally::Type::chickLeft].speed = 90.f;
		data[Ally::Type::chickLeft].directions.push_back(Direction(Ally::Type::chickLeft));
		data[Ally::Type::chickLeft].source = sf::Vector2i(0, 5);
		data[Ally::Type::chickLeft].endOfFrame = 64;
			 			 
		data[Ally::Type::chickRight].texture = TextureID::Animals;
		data[Ally::Type::chickRight].textureRect = sf::IntRect(192, 0, 32, 32);
		data[Ally::Type::chickRight].speed = 90.f;
		data[Ally::Type::chickRight].directions.push_back(Direction(Ally::Type::chickRight));
		data[Ally::Type::chickRight].source = sf::Vector2i(0, 6);
		data[Ally::Type::chickRight].endOfFrame = 64;

		data[Ally::Type::chickUp].texture = TextureID::Animals;
		data[Ally::Type::chickUp].textureRect = sf::IntRect(224, 0, 32, 32);
		data[Ally::Type::chickUp].speed = 90.f;
		data[Ally::Type::chickUp].directions.push_back(Direction(Ally::Type::chickLeft));
		data[Ally::Type::chickUp].source = sf::Vector2i(0, 7);
		data[Ally::Type::chickUp].endOfFrame = 64;
			 
		data[Ally::Type::seagullDown].texture = TextureID::Animals;
		data[Ally::Type::seagullDown].textureRect = sf::IntRect(0, 96, 32, 32);
		data[Ally::Type::seagullDown].speed = 90.f;
		data[Ally::Type::seagullDown].directions.push_back(Direction(Ally::Type::seagullDown));
		data[Ally::Type::seagullDown].source = sf::Vector2i(3, 0);
		data[Ally::Type::seagullDown].endOfFrame = 160;
			 			 
		data[Ally::Type::seagullLeft].texture = TextureID::Animals;
		data[Ally::Type::seagullLeft].textureRect = sf::IntRect(32, 96, 32, 32);
		data[Ally::Type::seagullLeft].speed = 90.f;
		data[Ally::Type::seagullLeft].directions.push_back(Direction(Ally::Type::seagullDown));
		data[Ally::Type::seagullLeft].source = sf::Vector2i(3, 1);
		data[Ally::Type::seagullLeft].endOfFrame = 160;
						 
		data[Ally::Type::seagullRight].texture = TextureID::Animals;
		data[Ally::Type::seagullRight].textureRect = sf::IntRect(64, 96, 32, 32);
		data[Ally::Type::seagullRight].speed = 90.f;
		data[Ally::Type::seagullRight].directions.push_back(Direction(Ally::Type::seagullUp));
		data[Ally::Type::seagullRight].source = sf::Vector2i(3, 2);
		data[Ally::Type::seagullRight].endOfFrame = 160;
			 			 
		data[Ally::Type::seagullUp].texture = TextureID::Animals;
		data[Ally::Type::seagullUp].textureRect = sf::IntRect(96, 96, 32, 32);
		data[Ally::Type::seagullUp].speed = 90.f;
		data[Ally::Type::seagullUp].directions.push_back(Direction(Ally::Type::seagullUp));
		data[Ally::Type::seagullUp].source = sf::Vector2i(3, 3);
		data[Ally::Type::seagullUp].endOfFrame = 160;

		return data;
	}

	std::map<Enemy::Type, EnemyData> initializeEnemyData()
	{
		std::map<Enemy::Type, EnemyData> data;

		data[Enemy::Type::wBirdDown].texture = TextureID::Animals;
		data[Enemy::Type::wBirdDown].textureRect = sf::IntRect( 0, 192, 32, 32);
		data[Enemy::Type::wBirdDown].speed = 90.f;
		data[Enemy::Type::wBirdDown].directions.push_back(Direction(Enemy::Type::wBirdDown));
		data[Enemy::Type::wBirdDown].source = sf::Vector2i(6, 0);
		data[Enemy::Type::wBirdDown].endOfFrame = 256;

		data[Enemy::Type::wBirdLeft].texture = TextureID::Animals;
		data[Enemy::Type::wBirdLeft].textureRect = sf::IntRect(32, 192, 32, 32);
		data[Enemy::Type::wBirdLeft].speed = 90.f;
		data[Enemy::Type::wBirdLeft].directions.push_back(Direction(Enemy::Type::wBirdLeft));
		data[Enemy::Type::wBirdLeft].source = sf::Vector2i(6, 1);
		data[Enemy::Type::wBirdLeft].endOfFrame = 256;

		data[Enemy::Type::wBirdRight].texture = TextureID::Animals;
		data[Enemy::Type::wBirdRight].textureRect = sf::IntRect(64, 192, 32, 32);
		data[Enemy::Type::wBirdRight].speed = 90.f;
		data[Enemy::Type::wBirdRight].directions.push_back(Direction(Enemy::Type::wBirdRight));
		data[Enemy::Type::wBirdRight].source = sf::Vector2i(6, 2);
		data[Enemy::Type::wBirdRight].endOfFrame = 256;

		data[Enemy::Type::wBirdUp].texture = TextureID::Animals;
		data[Enemy::Type::wBirdUp].textureRect = sf::IntRect(96, 192, 32, 32);
		data[Enemy::Type::wBirdUp].speed = 90.f;
		data[Enemy::Type::wBirdUp].directions.push_back(Direction(Enemy::Type::wBirdUp));
		data[Enemy::Type::wBirdUp].source = sf::Vector2i(6, 3);
		data[Enemy::Type::wBirdUp].endOfFrame = 256;

		data[Enemy::Type::mouseDown].texture = TextureID::Animals;
		data[Enemy::Type::mouseDown].textureRect = sf::IntRect(0, 288, 32, 32);
		data[Enemy::Type::mouseDown].speed = 90.f;
		data[Enemy::Type::mouseDown].directions.push_back(Direction(Enemy::Type::mouseDown));
		data[Enemy::Type::mouseDown].source = sf::Vector2i(9, 0);
		data[Enemy::Type::mouseDown].endOfFrame = 352;

		data[Enemy::Type::mouseLeft].texture = TextureID::Animals;
		data[Enemy::Type::mouseLeft].textureRect = sf::IntRect(32, 288, 32, 32);
		data[Enemy::Type::mouseLeft].speed = 90.f;
		data[Enemy::Type::mouseLeft].directions.push_back(Direction(Enemy::Type::mouseLeft));
		data[Enemy::Type::mouseLeft].source = sf::Vector2i(9, 1);
		data[Enemy::Type::mouseLeft].endOfFrame = 352;

		data[Enemy::Type::mouseRight].texture = TextureID::Animals;
		data[Enemy::Type::mouseRight].textureRect = sf::IntRect(64, 288, 32, 32);
		data[Enemy::Type::mouseRight].speed = 90.f;
		data[Enemy::Type::mouseRight].directions.push_back(Direction(Enemy::Type::mouseRight));
		data[Enemy::Type::mouseRight].source = sf::Vector2i(9, 2);
		data[Enemy::Type::mouseRight].endOfFrame = 352;

		data[Enemy::Type::mouseUp].texture = TextureID::Animals;
		data[Enemy::Type::mouseUp].textureRect = sf::IntRect(96, 288, 32, 32);
		data[Enemy::Type::mouseUp].speed = 90.f;
		data[Enemy::Type::mouseUp].directions.push_back(Direction(Enemy::Type::mouseUp));
		data[Enemy::Type::mouseUp].source = sf::Vector2i(9, 3);
		data[Enemy::Type::mouseUp].endOfFrame = 352;

		data[Enemy::Type::roosterDown].texture = TextureID::Animals;
		data[Enemy::Type::roosterDown].textureRect = sf::IntRect(128, 96, 32, 32);
		data[Enemy::Type::roosterDown].speed = 90.f;
		data[Enemy::Type::roosterDown].directions.push_back(Direction(Enemy::Type::raccoonDown));
		data[Enemy::Type::roosterDown].source = sf::Vector2i(3, 4);
		data[Enemy::Type::roosterDown].endOfFrame = 160;

		data[Enemy::Type::roosterLeft].texture = TextureID::Animals;
		data[Enemy::Type::roosterLeft].textureRect = sf::IntRect(160, 96, 32, 32);
		data[Enemy::Type::roosterLeft].speed = 90.f;
		data[Enemy::Type::roosterLeft].directions.push_back(Direction(Enemy::Type::roosterLeft));
		data[Enemy::Type::roosterLeft].source = sf::Vector2i(3, 5);
		data[Enemy::Type::roosterLeft].endOfFrame = 160;

		data[Enemy::Type::roosterRight].texture = TextureID::Animals;
		data[Enemy::Type::roosterRight].textureRect = sf::IntRect(192, 96, 32, 32);
		data[Enemy::Type::roosterRight].speed = 90.f;
		data[Enemy::Type::roosterRight].directions.push_back(Direction(Enemy::Type::roosterRight));
		data[Enemy::Type::roosterRight].source = sf::Vector2i(3, 6);
		data[Enemy::Type::roosterRight].endOfFrame = 160;

		data[Enemy::Type::roosterUp].texture = TextureID::Animals;
		data[Enemy::Type::roosterUp].textureRect = sf::IntRect(224, 96, 32, 32);
		data[Enemy::Type::roosterUp].speed = 90.f;
		data[Enemy::Type::roosterUp].directions.push_back(Direction(Enemy::Type::roosterUp));
		data[Enemy::Type::roosterUp].source = sf::Vector2i(3, 7);
		data[Enemy::Type::roosterUp].endOfFrame = 160;

		data[Enemy::Type::raccoonDown].texture = TextureID::Raccoon;
		data[Enemy::Type::raccoonDown].textureRect = sf::IntRect(0, 0, 32, 32);
		data[Enemy::Type::raccoonDown].speed = 90.f;
		data[Enemy::Type::raccoonDown].directions.push_back(Direction(Enemy::Type::raccoonDown));
		data[Enemy::Type::raccoonDown].source = sf::Vector2i(0, 0);
		data[Enemy::Type::raccoonDown].endOfFrame = 64;

		data[Enemy::Type::raccoonLeft].texture = TextureID::Raccoon;
		data[Enemy::Type::raccoonLeft].textureRect = sf::IntRect(32, 0, 32, 32);
		data[Enemy::Type::raccoonLeft].speed = 90.f;
		data[Enemy::Type::raccoonLeft].directions.push_back(Direction(Enemy::Type::raccoonLeft));
		data[Enemy::Type::raccoonLeft].source = sf::Vector2i(0, 1);
		data[Enemy::Type::raccoonLeft].endOfFrame = 64;

		data[Enemy::Type::raccoonRight].texture = TextureID::Raccoon;
		data[Enemy::Type::raccoonRight].textureRect = sf::IntRect(64, 0, 32, 32);
		data[Enemy::Type::raccoonRight].speed = 90.f;
		data[Enemy::Type::raccoonRight].directions.push_back(Direction(Enemy::Type::raccoonRight));
		data[Enemy::Type::raccoonRight].source = sf::Vector2i(0, 2);
		data[Enemy::Type::raccoonRight].endOfFrame = 64;

		data[Enemy::Type::raccoonUp].texture = TextureID::Raccoon;
		data[Enemy::Type::raccoonUp].textureRect = sf::IntRect(96, 0, 32, 32);
		data[Enemy::Type::raccoonUp].speed = 90.f;
		data[Enemy::Type::raccoonUp].directions.push_back(Direction(Enemy::Type::raccoonUp));
		data[Enemy::Type::raccoonUp].source = sf::Vector2i(0, 3);
		data[Enemy::Type::raccoonUp].endOfFrame = 64;

		return data;
	}
}