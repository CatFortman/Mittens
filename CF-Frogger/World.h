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

#include "SFML\graphics.hpp"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "Plane.h"
#include "Vehicle.h"
#include "RiverObject.h"
#include "SpriteNode.h"
#include "TextureHolder.h"
#include "Map.h"
#include "MapSpriteNode.h"
#include "Switch.h"

#include <vector>
#include <array>

namespace GEX
{
	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2);

	class World
	{
	public:

		explicit		World(sf::RenderWindow& window);
		~World();
		World&			operator=(const World&) = delete;

		void			update(sf::Time deltaTime);

		void			setView();

		void			draw();
		Cat*			getPlayer() { return _player; }
		CommandQueue&	getCommandQueue();

		bool			hasAlivePlayer() const;
		bool			hasReachFinish() const;

	private:

	/*	struct SpawnPointVehicle
		{
			SpawnPointVehicle(Vehicle::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y) {}
			Vehicle::Type type;
			float		x;
			float		y;
		};*/


	/*	struct SpawnPointRiverObject
		{
			SpawnPointRiverObject(RiverObject::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y) {}
			RiverObject::Type type;
			float		x;
			float		y;
		};*/

		struct TileCollisionElement {
			TileCollisionElement(float l_area, TileInfo* l_info,
				const sf::FloatRect& l_bounds) :m_area(l_area),
				m_tile(l_info), m_tileBounds(l_bounds) {}
			float m_area;
			TileInfo* m_tile;
			sf::FloatRect m_tileBounds;
		};

	private:

		void			buildScene();

		sf::FloatRect	getViewBounds() const;
		sf::FloatRect	getBattlefieldBounds() const;

		void			adaptPlayerPostition();

		void			respawnPlayer();

		void			spawnEnemies();
		void			addEnemies();
	//	void			addEnemy(Vehicle::Type type, float relX, float relY);
		//void			addEnemy(RiverObject::Type type, float relX, float relY);
		//void			addEnemy(SpawnPointVehicle point);
		//void			addEnemy(SpawnPointRiverObject point);

		float			interSectionAmount(sf::FloatRect a, sf::FloatRect b);
		void			handleEntityCollisions();
		void			checkTileCollions();
		void			handleTileCollisions();

		void			destroyEnemiesOutsideView();

	private:

		enum _Layers
		{
			Background,
			Ground,
			Road,
			RiverNode,
			LayerCount
		};

		sf::RenderWindow&					_window;
		sf::View							_worldView;
		SceneNode							_sceneGraph;

		std::array<SceneNode*, LayerCount>	_sceneLayers;
		CommandQueue						_queue;
		sf::FloatRect						_worldBounds;
		sf::Vector2f						_spawnPosition;
		float								_scrollSpeed;
		Cat*								_player;

		sf::Clock							_vehicleSpawnTimer;
		sf::Clock							_riverSpawnTimer;

	//	std::deque<SpawnPointVehicle>		_vehicleSpawnPoints;
	//	std::deque<SpawnPointRiverObject>	_riverSpawnPoints;
	//	std::vector<Vehicle*>				_vehicles;
	//	std::vector<Vehicle*>				_activeEnemies;

		//std::unique_ptr<MapSpriteNode>		_mapNode;
		Map*								_mGameMap;

		std::vector<TileCollisionElement>   _tileCollisions;

		Switch*								_switch;
		//std::vector<Switch*>				_switches;

		std::vector<SpriteNode*>			_lives;
		int									_lifeX;
	};
}
