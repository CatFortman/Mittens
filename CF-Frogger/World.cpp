/**
@file
@author  Cat Fortman
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "World.h"
#include "Plane.h"
#include "RiverObject.h"
#include "TextureHolder.h"
#include "SpriteNode.h"
#include "ParticleNode.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <iostream>

namespace GEX
{
	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();


		if (type1 & category1 && type2 & category2)
		{
			return true;
		}
		else if (type1 & category2 && type2 & category1)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else
		{
			return false;
		}
	}

	World::World(sf::RenderWindow& window) :
		_window(window),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(0.f, 0.f, 2240, 2560), //2240 2560
		_spawnPosition(_worldView.getSize().x / 2.f, _worldView.getSize().y / 2),
		_vehicleSpawnTimer(),
		_riverSpawnTimer(),
		_queue(),
		_mGameMap(),
		_player(nullptr)
		//_switch(nullptr)
	{
		buildScene();

		//sets the view to the bottom since we will scroll upwards
		//_worldView.setCenter(_spawnPosition);
	}


	World::~World()
	{
		_mGameMap = nullptr;
	}

	void World::update(sf::Time deltaTime)
	{
		// run all the commands
		while (!_queue.isEmpty())
		{
			_sceneGraph.onCommand(_queue.pop(), sf::Time::Zero);
		}

		//set the view within map
		setView();

		destroyEnemiesOutsideView();
		// handle collsions
		handleCollisions();

		// remove all destroyed enemies
		_sceneGraph.removeWrecks();

		// update cat life positions
		_lifeX = 40;
		std::vector<SpriteNode*>::iterator iter;
		for (iter = _lives.begin(); iter != _lives.end(); iter++)
		{
			(*iter)->setPosition((_window.getSize().x - _lifeX), (_window.getSize().y - 310));
			_lifeX += 25;
		}

		// update switch spins
//		_switch->setType(_switch->getType());

		//spawnEnemies();
		//movement

		_mGameMap->Update(deltaTime.asSeconds(), _window);

		_sceneGraph.update(deltaTime, getCommandQueue());
		//std::cout << "( " << _player->getPosition().x << "' " << _player->getPosition().y << " )" << std::endl;

		adaptPlayerPostition();
	}

	void World::setView()
	{
		_worldView.setCenter(_player->getPosition());
		//get players posiiton and set current view to  center on him

		sf::Vector2f player_pos = _player->getPosition();

		//now get view center and size and make sure it isnt goign off the map

		sf::Vector2f view_center = _worldView.getCenter();
		sf::Vector2f view_size = _worldView.getSize();

		if (player_pos.y - (view_size.y / 2) < 0) //check to see if viewport y is less than 0 on y axis
		{
			view_center.y = view_size.y / 2;
			view_center.x = player_pos.x;
			_worldView.setCenter(view_center);
		}

		if (player_pos.y + (view_size.y / 2) > 2560) //check to see if viewport y is greater than height.
		{
			view_center.y = 2560 - (view_size.y / 2);
			view_center.x = player_pos.x;
			_worldView.setCenter(view_center);
		}

		if (player_pos.x - (view_size.x / 2) < 0) //check to see if viewport  x will be less than 0 on x axis
		{
			view_center.x = view_size.x / 2;
			//view_center.y = player_pos.y;
			_worldView.setCenter(view_center);
		}

		if (player_pos.x + (view_size.x / 2) > 2240) //check to see if viewport x is greater than map size 2115
		{
			view_center.x = 2240 - (view_size.x / 2);
			//view_center.y = player_pos.y;
			_worldView.setCenter(view_center);
		}

	}

	void World::adaptPlayerPostition()
	{
		// Keep player's position inside the screen bounds, 
		// at least borderDistance units from the border

		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 15.f;

		sf::Vector2f position = _player->getPosition();
		position.x = std::max(position.x, _worldBounds.left + borderDistance);
		position.x = std::min(position.x, _worldBounds.left + _worldBounds.width - borderDistance);
		position.y = std::max(position.y, _worldBounds.top + borderDistance);
		position.y = std::min(position.y, _worldBounds.top + _worldBounds.height - borderDistance);
		_player->setPosition(position);

		/*if (_player->isRespawing())
		{
			respawnPlayer();
			_player->setIsRespawning(false);
		}*/

		_player->setVelocity(0, 0);

		//_worldView.setCenter(_player->getPosition());
		_window.setView(_worldView);
	}

	void World::draw()
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);
	}

	CommandQueue & World::getCommandQueue()
	{
		return _queue;
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}

	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100;
		bounds.height += 100;
		return bounds;
	}

	void World::spawnEnemies()
	{
		//auto spawnV = _vehicleSpawnPoints.back();	// get's the spawn point and vehicle from vector
		//auto spawnVPos = spawnV;	// keeps the spawn
		//std::unique_ptr<Vehicle> temp(new Vehicle(spawnV.type)); // creates the vehicle with spawn position

		// if it has been five seconds or the vehicle is not on the map then add it to the map 
		/*if ((_vehicleSpawnTimer.getElapsedTime() >= sf::seconds(1)) || (!getBattlefieldBounds().intersects(temp->getBoundingRect())))
		{
			_vehicles.push_back(temp.get());

			temp->setPosition(spawnV.x, spawnV.y);
			_sceneLayers[Ground]->attatchChild(std::move(temp));
			_vehicleSpawnPoints.pop_back();
			_vehicleSpawnPoints.push_front(spawnVPos);

			_vehicleSpawnTimer.restart();
		}

		auto spawnR = _riverSpawnPoints.back();	// get's the spawn point and river from vector
		auto spawnRPos = spawnR;	// keeps the spawn
		std::unique_ptr<RiverObject> tempR(new RiverObject(spawnR.type)); // creates the river object with spawn position

																 // if it has been five seconds or the vehicle is not on the map then add it to the map
		if ((_riverSpawnTimer.getElapsedTime() >= sf::seconds(1)) || (!getBattlefieldBounds().intersects(tempR->getBoundingRect())))
		{
			//_vehicles.push_back(temp.get());

			tempR->setPosition(spawnR.x, spawnR.y);
			_sceneLayers[Ground]->attatchChild(std::move(tempR));
			_riverSpawnPoints.pop_back();
			_riverSpawnPoints.push_front(spawnRPos);

			_riverSpawnTimer.restart();
		}*/
	}

	void World::addEnemies()
	{
		// add enemy spawn points
	/*	addEnemy(Vehicle::Type::Car, 250, 120);
		addEnemy(Vehicle::Type::RaceCarL, 250, 40);
		addEnemy(Vehicle::Type::RaceCarR, -235, 160);
		addEnemy(Vehicle::Type::Tractor, -235, 80);
		addEnemy(Vehicle::Type::Truck, 250, 200);

		addEnemy(RiverObject::Type::tree1, -235, 360);
		addEnemy(RiverObject::Type::tree1, -235, 320);
		addEnemy(RiverObject::Type::tree2, -235, 440);
		addEnemy(RiverObject::Type::threeTurtles1, 235, 280);
		addEnemy(RiverObject::Type::turtles1, 235, 400);

		//std::sort(_vehicleSpawnPoints.begin(), _vehicleSpawnPoints.end(), [](SpawnPointVehicle lhs, SpawnPointVehicle rhs) {return lhs.y < rhs.y;	});
		std::sort(_riverSpawnPoints.begin(), _riverSpawnPoints.end(), [](SpawnPointRiverObject lhs, SpawnPointRiverObject rhs) {return lhs.y < rhs.y;	});
	*/
	}

	/*void World::addEnemy(Vehicle::Type type, float relX, float relY)
	{
		addEnemy(SpawnPointVehicle(type, relX, relY));
	}*/

	/*void World::addEnemy(RiverObject::Type type, float relX, float relY)
	{
		addEnemy(SpawnPointRiverObject(type, relX, relY));
	}*/

	/*void World::addEnemy(SpawnPointVehicle point)
	{
		point.x = _spawnPosition.x + point.x;
		point.y = _spawnPosition.y - point.y;
		_vehicleSpawnPoints.push_back(point);
	}*/

	/*void World::addEnemy(SpawnPointRiverObject point)
	{
		point.x = _spawnPosition.x + point.x;
		point.y = _spawnPosition.y - point.y;
		_riverSpawnPoints.push_back(point);
	}*/

	void World::buildScene()
	{
		// LAYER NODES FOR SCENE GRAPH
		for (std::size_t i = 0; i < LayerCount; i++)
		{
			Category::type category = (i == Ground) ? Category::sceneGroundLayer : Category::none;
			SceneNode::ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attatchChild(std::move(layer));
		}

		// Map
		_mGameMap->LoadMap("Media/Map1.map");
		_mapNode->setGameMap(*_mGameMap);
		_sceneLayers[Ground]->attatchChild(std::move(_mapNode));

		//Switches


		// Cat lives
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Life);
		sf::IntRect textureRect = sf::IntRect(0, 0, 32, 42);

		std::unique_ptr<SpriteNode> CatLife1(new SpriteNode(texture, textureRect));
		SpriteNode* _CatLife1 = CatLife1.get();
		CatLife1->setPosition((_worldView.getSize().x - 90), (_worldView.getSize().y - 310));
		_sceneLayers[Ground]->attatchChild(std::move(CatLife1));


		std::unique_ptr<SpriteNode> CatLife2(new SpriteNode(texture, textureRect));
		SpriteNode* _CatLife2 = CatLife2.get();
		CatLife2->setPosition((_worldView.getSize().x - 65), (_worldView.getSize().y - 310));
		_sceneLayers[Ground]->attatchChild(std::move(CatLife2));

		std::unique_ptr<SpriteNode> CatLife3(new SpriteNode(texture, textureRect));
		SpriteNode* _CatLife3 = CatLife3.get();
		CatLife3->setPosition((_worldView.getSize().x - 40), (_worldView.getSize().y - 310));
		_sceneLayers[Ground]->attatchChild(std::move(CatLife3));

		_lives.push_back(_CatLife1);
		_lives.push_back(_CatLife2);
		_lives.push_back(_CatLife3);

		// add the enemies
		//addEnemies();

		// Switches
		std::unique_ptr<Switch> blue1(new Switch(Switch::Type::GreenLeft));
		_switch = blue1.get();
		_switch->setPosition(_spawnPosition);
		_sceneLayers[Ground]->attatchChild(std::move(blue1));

		// Idle
		std::unique_ptr<Cat> Cat(new Cat(Cat::Type::Down));
		_player = Cat.get();
		_player->setPosition(_spawnPosition.x + 50, _spawnPosition.y);

		_sceneLayers[Ground]->attatchChild(std::move(Cat));

		std::unique_ptr<Enemy> raccoon(new Enemy(Enemy::Type::raccoonDown));
		Enemy* r = raccoon.get();
		r->setPosition(_spawnPosition);
		_sceneLayers[Ground]->attatchChild(std::move(raccoon));

		std::unique_ptr<Ally> frog(new Ally(Ally::Type::bunnyDown));
		Ally* f = frog.get();
		f->setPosition((_spawnPosition.x - 80), (_spawnPosition.y + 40));
		_sceneLayers[Ground]->attatchChild(std::move(frog));
	}

	void World::handleCollisions()
	{
		// build list of all pairs of colliding scenenodes
		std::set<SceneNode::pair> collisionPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);

		if (collisionPairs.size() != 0)
		{
			std::cout << collisionPairs.size() << std::endl;
		}

		// collision: switch is destroyed
		for (SceneNode::pair pair : collisionPairs)
		{
			if (matchesCategories(pair, Category::playerCharacter, Category::switchSprite))
			{
				// safe downcasts
				auto& player = static_cast<Cat&>(*pair.first);
				auto& switchSprite = static_cast<Switch&>(*pair.second);

				// collision: Switch is destroyed
				switchSprite.destroy();
				_mapNode->loadNextGameMap();
			}
		}


		// for each scenenode pair
		for (SceneNode::pair pair : collisionPairs)
		{
			//if (matchesCategories(pair, Category::playerCharacter, Category::vehicle))
			//{
			//	// safe downcasts
			//	auto& player = static_cast<Cat&>(*pair.first);
			//	auto& enemy = static_cast<Vehicle&>(*pair.second);

			//	// collision: Catger is destroyed
			//	if (player.isDying() == false)
			//	{
			//		player.setIsDying(true);
			//	}
			//}
		}
	}

	void World::respawnPlayer()
	{
		_player->setPosition(_spawnPosition);
	}

	void World::destroyEnemiesOutsideView()
	{
		/*Command command;
		command.category = Category::vehicle | Category::logs | Category::turtles;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
		{
			if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
				e.destroy();
		});
		_queue.push(command);*/
	}

	bool World::hasAlivePlayer() const
	{
		return !_player->isMarkedForRemoval();
	}

	bool World::hasReachFinish() const
	{
		return !_worldBounds.contains(_player->getPosition());
	}
}