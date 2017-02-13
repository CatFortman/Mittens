#include "State.h"
#include "StateStack.h"
#include "MusicPlayer.h"
#include "TileInfo.h"

namespace GEX
{
	State::Context::Context(sf::RenderWindow& window, PlayerControl& player, MusicPlayer& music, SoundPlayer& soundEffect, TileInfo& tileInfo) :
		window(&window),
		player(&player),
		music(&music),
		soundEffect(&soundEffect),
		tileInfo(&tileInfo)
	{}

	State::State(StateStack& stack, Context context) :
		_stack(&stack),
		_context(context)
	{}

	State::~State()
	{}

	void State::requestStackPush(StateID stateID)
	{
		_stack->pushState(stateID);
	}

	void State::requestStackPop()
	{
		_stack->popState();
	}

	void State::requestStateClear()
	{
		_stack->clearStates();
	}

	State::Context State::getContext() const
	{
		return _context;
	}
}