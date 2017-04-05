/**
@file
@author  Cat Fortman
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#pragma once
#include "ResourceIdentifiers.h"
#include "Plane.h"
#include "Partcile.h"
#include "Vehicle.h"
#include "RiverObject.h"
#include "Switch.h"

#include <map>
#include <vector>

namespace GEX
{
	struct Direction
	{
		Direction(Enemy::Type et);
		Enemy::Type eType;

		Direction(Ally::Type at);
		Ally::Type aType;
	};

	struct CatData
	{
		int						hitPoints;
		TextureID				texture;
		sf::IntRect				textureRect;
		sf::Vector2i			source;
	};

	struct ParticleData
	{
		sf::Color				color;
		sf::Time				lifetime;
	};

	struct EnemyData
	{
		TextureID				texture;
		std::vector<Direction>  directions; // vector describes path of the enemies
		sf::IntRect				textureRect;
		float					speed;
		sf::Vector2i			source;
		int						endOfFrame; // end of sprite rows
	};

	struct AllyData
	{
		TextureID				texture;
		std::vector<Direction>  directions; // vector describes path of the allies
		sf::IntRect				textureRect;
		float					speed;
		sf::Vector2i			source;     // keep track of x and y of sprite 
		int						endOfFrame; // end of sprite rows
	};

	struct SwitchData
	{
		int						hitPoints;
		TextureID				texture;
		sf::IntRect				textureRect;
	};

	std::map<Cat::Type, CatData>					initializeCatData();
	std::map<Particle::Type, ParticleData>			initializeParticleData();
	std::map<Enemy::Type, EnemyData>				initializeEnemyData();
	std::map<Ally::Type, AllyData>					initializeAllyData();
	std::map<Switch::Type, SwitchData>				initializeSwitchData();
}
