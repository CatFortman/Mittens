#include "SoundPlayer.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <cassert>


#include <cmath>



namespace GEX
{

	namespace
	{
		// Sound coordinate system, point of view of a player in front of the screen:
		// X = left; Y = up; Z = back (out of the screen)
		const float Volume = 100.f;
		const float ListenerZ = 300.f;
		const float Attenuation = 1.f;
		const float MinDistance2D = 200.f;
		const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
	}

	SoundPlayer::SoundPlayer()
	{

		// Listener points towards the screen (default in SFML)
		sf::Listener::setDirection(0.f, 0.f, -1.f);
	}

	void SoundPlayer::play(SoundEffectID effect)
	{
		play(effect, getListenerPosition());
	}

	void SoundPlayer::play(SoundEffectID effect, sf::Vector2f position)
	{

		sf::Sound soundEffect(SoundBufferHolder::getInstance().get(effect));
		_sounds.push_back(soundEffect);

		sf::Sound& sound = _sounds.back();

		sound.setBuffer(SoundBufferHolder::getInstance().get(effect));
		sound.setVolume(Volume);
		sound.setPosition(position.x, -position.y, 0.f);
		sound.setAttenuation(Attenuation);
		sound.setMinDistance(MinDistance3D);

		sound.play();
	}

	void SoundPlayer::removeStoppedSounds()
	{
		_sounds.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
	}

	void SoundPlayer::setListenerPosition(sf::Vector2f position)
	{
		sf::Listener::setPosition(position.x, -position.y, ListenerZ);
	}

	sf::Vector2f SoundPlayer::getListenerPosition() const
	{
		sf::Vector3f position = sf::Listener::getPosition();
		return sf::Vector2f(position.x, -position.y);
	}

}