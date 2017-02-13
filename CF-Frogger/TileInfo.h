#pragma once

#include "SFML\graphics.hpp"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "SpriteNode.h"
#include "TextureHolder.h"


namespace GEX {

	using TitleID = unsigned int;

	enum Sheet { tileSize = 64, sheetWidth = 320, sheetHeight = 448 };

	struct TileInfo {
		TileInfo(const std::string& lTexture, TitleID lId = 0)
			: mId(0), mDeadly(false)
		{
			if (lTexture == "") { mId = lId; return; }
			mTexture = lTexture;
			mId = lId;
			mSprite.setTexture(TextureHolder::getInstance().get(TextureID::Map));
			sf::IntRect tileBoundaries(mId % (Sheet::sheetWidth / Sheet::tileSize) * Sheet::tileSize,
				mId / (Sheet::sheetHeight / Sheet::tileSize)*Sheet::tileSize,
				Sheet::tileSize, Sheet::tileSize);
			mSprite.setTextureRect(tileBoundaries);
		}


		~TileInfo() {
			if (mTexture == "") { return; }
		}

		sf::Sprite mSprite;

		TitleID mId;
		std::string mName;
		bool mDeadly;

		std::string mTexture;

	};
}