#pragma once
#include "SceneNode.h"
#include "Map.h"

namespace GEX 
{
	class MapSpriteNode : public SceneNode
	{
	public:
		MapSpriteNode();
		~MapSpriteNode();
	
	public:

		void setGameMap(Map& map);
		void loadNextGameMap();

	private:

		void drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const override;

	private:

		Map _map;
	};
}
