#include "Map.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
const int MAP_MAX_COLUMNS = 35;
const int MAP_MAX_ROWS = 40;
namespace GEX {

	Map::Map() : m_maxMapSize(MAP_MAX_ROWS, MAP_MAX_COLUMNS), m_tileCount(0), m_tileSetCount(0), m_loadNextMap(false), m_tileSet(), m_tileMap()
	{
		//default tile?
		//gamemap =?		
		LoadTiles("Tiles.cfg");
	}

	Map::~Map()
	{
		PurgeMap();
		PurgeTileSet();
		//m_context->m_gameMap = nullptr;
	}

	Tile* Map::GetTile(unsigned int l_x, unsigned int l_y) const
	{
		auto itr = m_tileMap.find(ConvertCoords(l_x, l_y));
		return(itr != m_tileMap.end() ? itr->second : nullptr);
	}

	TileInfo* Map::GetDefaultTile()
	{
		return &m_defaultTile;
	}

	unsigned int Map::ConvertCoords(const unsigned int& l_x, const unsigned int& l_y) const
	{
		return (l_x * m_maxMapSize.x) + l_y; // Row-major.
	}

	const sf::Vector2u& Map::GetMapSize()const
	{
		return m_maxMapSize;
	}

	const sf::Vector2f& Map::GetPlayerStart()const
	{
		return m_playerStart;
	}

	void Map::LoadMap(const std::string & path)
	{
		std::ifstream file;
		file.open(path);
		if (!file.is_open()) {
			std::cout << "! Failed loading map file: "
				<< path << std::endl;
			return;
		}
		std::string line;
		while (std::getline(file, line))
		{
			std::cout << line << std::endl;

			if (line[0] == '|') { continue; }
			std::stringstream keystream(line);
			std::string type;
			keystream >> type;
			if (type == "TILE")
			{
				int tileId = 0;
				keystream >> tileId;
				if (tileId < 0)
				{
					std::cout << "! Bad tile id: " << tileId << std::endl;
				}
				auto itr = m_tileSet.find(tileId);
				if (itr == m_tileSet.end())
				{
					std::cout << "! Tile id(" << tileId << ") was not found in tileset." << std::endl;
				}
				sf::Vector2i tileCoords;
				keystream >> tileCoords.x >> tileCoords.y;
				if (tileCoords.x > m_maxMapSize.x || tileCoords.y > m_maxMapSize.y)
				{
					std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
				}
				Tile* tile = new Tile();  // Bind properties of a tile from a set.  
				tile->mProperties = itr->second;

				std::cout << "Tile " << ConvertCoords(tileCoords.x, tileCoords.y) << std::endl;
				if (ConvertCoords(tileCoords.x, tileCoords.y) > 1395)
					std::cout << "Tile " << ConvertCoords(tileCoords.x, tileCoords.y) << std::endl;
				if (!m_tileMap.emplace(ConvertCoords(tileCoords.x, tileCoords.y), tile).second)
				{    // Duplicate tile detected!    
					std::cout << "! Duplicate tile in Load Map ! : " << tileCoords.x << "" << tileCoords.y << std::endl;
					delete tile;
					tile = nullptr;
				}
			}
			else if (type == "SIZE")
			{
				keystream >> m_maxMapSize.x >> m_maxMapSize.y;
			}
			else if (type == "NEXTMAP")
			{
				keystream >> m_nextMap;
			}
		}
	}

	void Map::Update(float l_dT, sf::RenderWindow& window)
	{
		if (m_loadNextMap) {
			PurgeMap();
			m_loadNextMap = false;
			if (m_nextMap != "") {
				LoadMap("Media/" + m_nextMap);
			}
			/*else {
				m_currentState->GetStateManager()->SwitchTo(StateType::GameOver);
			}*/
			m_nextMap = "";
		}
	}

	void Map::Draw(sf::RenderTarget& window) const
	{
		sf::View view = window.getView();
		sf::FloatRect viewSpace = sf::FloatRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
		sf::Vector2i tileBegin(
			floor(viewSpace.top / Sheet::tileSize),
			floor(viewSpace.left / Sheet::tileSize));
		sf::Vector2i tileEnd(
			ceil((viewSpace.top + viewSpace.width) / Sheet::tileSize) + Sheet::tileSize,
			ceil((viewSpace.left + viewSpace.height) / Sheet::tileSize) +   Sheet::tileSize);
		unsigned int count = 0;
		for (int x = tileBegin.x; x <= tileEnd.x; ++x) {
			for (int y = tileBegin.y; y <= tileEnd.y; ++y) {
				if (x < 0 || y < 0) { continue; }
				Tile* tile = GetTile(x, y);
				if (!tile) { continue; }
				sf::Sprite& sprite = tile->mProperties->mSprite;
				sprite.setPosition((y * Sheet::tileSize), (x * Sheet::tileSize));

				window.draw(sprite);
				++count;
			}
		}
	}

	void Map::PurgeMap()
	{
		m_tileCount = 0;
		m_tileMap.clear();
	}

	void Map::PurgeTileSet()
	{
		for (auto &itr : m_tileSet) {
			delete itr.second;
		}
		m_tileSet.clear();
		m_tileSetCount = 0;
	}

	void Map::LoadTiles(const std::string& l_path)
	{
		std::ifstream file;
		file.open("Media/" + l_path);
		if (!file.is_open()) {
			std::cout << "! Failed loading tile set file: "
				<< l_path << std::endl;
			return;
		}
		std::string line;
		while (std::getline(file, line)) {
			if (line[0] == '|')
			{
				continue;
			}
			std::stringstream keystream(line);
			int tileId;
			keystream >> tileId;
			if (tileId < 0)
			{
				continue;
			}
			TileInfo* tile = new TileInfo("TileSheet", tileId);
			keystream >> tile->mName >> tile->mBlock >> tile->mDeadly;
			if (!m_tileSet.emplace(tileId, tile).second) {
				// Duplicate tile detected!
				std::cout << "! Duplicate tile type: " << tile->mName << std::endl;
				delete tile;
			}
		}
		file.close();
	}

	void Map::LoadNext() { m_loadNextMap = true; }
}
