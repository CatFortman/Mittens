#pragma once
namespace GEX 
{
	namespace Category
	{
		enum type {
			none = 0,		// 0000 0000
			playerCharacter = 1 << 0, // 0000 0001
			sceneGroundLayer = 1 << 1,	// 0000 0010
			enemy = 1 << 2,	// 0000 0100
			ally = 1 << 3, // 0000 1000
			switchSprite = 1 << 4, // 0001 0000
			SoundEffect = 1 << 5,	// 0010 0000
			ParticleSystem = 1 << 6	// 0100 0000

		};
	}
}