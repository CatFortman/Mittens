#pragma once
#include "SFML\graphics.hpp"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "SpriteNode.h"
#include "TextureHolder.h"
#include "Tile.h"
#include "TileInfo.h"
#include "PlayerControl.h"

#include <unordered_map>

namespace GEX {

	using TileID = unsigned int;
	using TileMap = std::unordered_map<TileID, Tile*>;
	using TileSet = std::unordered_map<TileID, TileInfo*>;

	class MapSpriteNode : public SceneNode
	{

	public:

		MapSpriteNode();
		~MapSpriteNode();
		Tile*					GetTile(unsigned int l_x, unsigned int l_y) const;
		TileInfo*				GetDefaultTile();
		//unsigned int			GetTileSize()const;
		const					sf::Vector2u& GetMapSize()const;
		const					sf::Vector2f& GetPlayerStart()const;
		void					LoadTiles(const std::string& l_path);
		void					LoadMap(const std::string& path);
		void					LoadNext();
		void					Update(float l_dT, sf::RenderWindow& window);
		void					Draw(sf::RenderTarget& window) const;
		void					PurgeMap();
		void					PurgeTileSet();

		void					drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const override;

	private:

		// Method for converting 2D coordinates to 1D ints.
		unsigned int			ConvertCoords(const unsigned int& l_x, const unsigned int& l_y) const;

	private:

		std::unordered_map<TileID, TileInfo*>					m_tileSet;
		TileMap													m_tileMap;
		TileInfo												m_defaultTile;
		sf::Vector2u											m_maxMapSize;
		sf::Vector2f											m_playerStart;
		unsigned int											m_tileCount;
		unsigned int											m_tileSetCount;
		std::string												m_nextMap;
		bool													m_loadNextMap;
	};
}
