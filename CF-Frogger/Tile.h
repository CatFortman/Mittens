#pragma once
#include "SFML\graphics.hpp"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "SpriteNode.h"
#include "TextureHolder.h"
#include "TileInfo.h"

namespace GEX{
	struct Tile{
		TileInfo* mProperties;
		bool mDeadly;
		bool mBlock;
	};
}

