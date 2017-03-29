#pragma once
#include <SFML/graphics.hpp>
#include "SceneNode.h"
#include "CommandQueue.h"
#include "SpriteNode.h"
#include "TextureHolder.h"

namespace GEX {

	using TileID = unsigned int;

	enum Sheet { tileSize = 64, sheetWidth = 320, sheetHeight = 576 };
	
	
	struct TileInfo {

		TileInfo() {}

		TileInfo(const std::string& lTexture, TileID lId = 0) : mId(0), mDeadly(false), mBlock(false)
		{
			if (lTexture == "") { mId = lId; return; }
			mTexture = lTexture;
			mId = lId;
			mSprite.setTexture(TextureHolder::getInstance().get(TextureID::Map));
			int top;

			if (mId <= 4)
			{
				top = 0;
			}
			else if (mId > 4 && mId < 10)
			{
				top = 64;
			}
			else if (mId >= 10 && mId < 15)
			{
				top = 128;
			}
			else if (mId >= 15 && mId < 20)
			{
				top = 192;
			}
			else if (mId >= 20 && mId < 25)
			{
				top = 256;
			}
			else if (mId >= 25 && mId < 30)
			{
				top = 320;
			}
			else if (mId >= 30 && mId < 35)
			{
				top = 384;
			}
			else if (mId >= 35 && mId < 40)
			{
				top = 448;
			}
			else 
			{
				top = 512;
			}


			sf::IntRect tileBoundaries(mId % (Sheet::sheetWidth / Sheet::tileSize) * Sheet::tileSize,    // 192, 128 ((255!))
			top,
			Sheet::tileSize, Sheet::tileSize);
	
			// id * row divided by 64
			// original top: mId / (Sheet::sheetHeight / Sheet::tileSize) * Sheet::tileSize 

			mSprite.setTextureRect(tileBoundaries);
		}


		~TileInfo() {
			if (mTexture == "") { return; }
		}

		sf::Sprite mSprite;

		TileID mId;
		std::string mName;
		bool mBlock;
		bool mDeadly;

		std::string mTexture;
	};
}