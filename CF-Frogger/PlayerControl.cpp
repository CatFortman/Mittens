#include "PlayerControl.h"
#include "Plane.h"
#include "Category.h"

namespace GEX 
{
	struct CatMover {
	
		CatMover(float vx, float vy, int direction) : velocity(vx, vy), dir(direction) {}
		void operator() (Cat& Cat, sf::Time) const {

			switch (dir) {
			case 0:
				Cat.setType(Cat::Type::Down);
				break;
			case 1:
				Cat.setType(Cat::Type::Left);
				break;
			case 2:
				Cat.setType(Cat::Type::Right);
				break;
			default:
				Cat.setType(Cat::Type::Up);
				break;
			}

			Cat.setVelocity(velocity);
		}

		int dir;
		float rotation;
		sf::Vector2f velocity;
	};

	PlayerControl::PlayerControl() :
		_missionStatus(MissionStatus::Active),
		_directionFacing(0)
	{
		initalizeKeyBindings();
		initalizeActionBindings();
	}

	void PlayerControl::setDirectionFacing(int dir)
	{
		_directionFacing = dir;
	}

	int PlayerControl::getDirectionFacing() const
	{
		return _directionFacing;
	}

	void PlayerControl::handleEvent(const sf::Event& events, CommandQueue & commands)
	{
		if (events.type == sf::Event::KeyPressed)
		{
			// check if key is bound to action
			// and that its not handled as a real event
			auto found = _keyBindings.find(events.key.code);
			if (found != _keyBindings.end() && !isRealTimeAction(found->second))
			{
				commands.push(_actionBindings[found->second]);
			}
		}
	}

	void PlayerControl::handleRealTimeInput(CommandQueue& commands)
	{
		for (auto pair : _keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
				commands.push(_actionBindings[pair.second]);
		}
	}

	bool PlayerControl::isRealTimeAction(Action action)
	{
		switch (action)
		{
		case Action::moveDown:
		case Action::moveLeft:
		case Action::moveRight:
		case Action::moveUp:
			return true;
		default:
			break;
		}
		return false;
	}

	void PlayerControl::initalizeKeyBindings()
	{
		_keyBindings[sf::Keyboard::A] = Action::moveLeft;
		_keyBindings[sf::Keyboard::D] = Action::moveRight;
		_keyBindings[sf::Keyboard::W] = Action::moveUp;
		_keyBindings[sf::Keyboard::S] = Action::moveDown;
	}

	void PlayerControl::initalizeActionBindings()
	{
		const float playerSpeed = 90;

		_actionBindings[Action::moveLeft].action		= derivedAction<Cat>(CatMover(-playerSpeed, 0, 1));
		_actionBindings[Action::moveRight].action       = derivedAction<Cat>(CatMover(playerSpeed, 0, 2));
		_actionBindings[Action::moveUp].action			= derivedAction<Cat>(CatMover(0, -playerSpeed, 3));
		_actionBindings[Action::moveDown].action		= derivedAction<Cat>(CatMover(0, playerSpeed, 0));
		
		for (auto& pair : _actionBindings)
			pair.second.category = Category::playerCharacter;
	}

	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		_missionStatus = status;
	}

	MissionStatus PlayerControl::getMissionStatus() const
	{
		return _missionStatus;
	}
}

