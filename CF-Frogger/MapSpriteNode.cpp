#include "MapSpriteNode.h"


namespace GEX 
{
	MapSpriteNode::MapSpriteNode()
	{
		//_map = map;
	}


	MapSpriteNode::~MapSpriteNode()
	{
	}

	void MapSpriteNode::setGameMap(Map& map)
	{
		_map = map;
	}

	void MapSpriteNode::loadNextGameMap()
	{
		_map.LoadNext();
	}

	void MapSpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		_map.Draw(target);
	}
}
