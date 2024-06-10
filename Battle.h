#pragma once


#include"PokemonTrainer.h"
#include"Engine.h"
#include"BattleState.h"
#include"BattleStarting.h"
#include"ResourceCache.h"

#include<memory>


class Battle {
	std::unique_ptr<BattleState> startingState;	//pocz¹tkowo zawiera nullptr
	std::unique_ptr<BattleState> state;			//pocz¹tkowo zawiera nullptr


	void preloadResources() {
		cache.bitmap("battle/largePokeball1.png");
		cache.bitmap("battle/largePokeball2.png");
		cache.soundSampleInstance("battle/battleStart.mp3");
		cache.soundSampleInstance("battle/battle.mp3");

		cache.bitmap("battle/bottomBorder.png");
		cache.bitmap("battle/smallPokeball.png");
		cache.bitmap("battle/topBorder.png");
		cache.font("battle/pokemon.ttf");

		cache.bitmap("battle/dust1.png");
		cache.bitmap("battle/dust2.png");
		cache.bitmap("battle/dust3.png");
		cache.bitmap("battle/dust4.png");
		cache.soundSample("battle/pokeballPoof.mp3");

		cache.bitmap("battle/wish.png");
		cache.soundSample("battle/wish.mp3");

		cache.soundSample("battle/dead.mp3");

		cache.soundSample("battle/lost.mp3");
		cache.soundSample("battle/win.mp3");
	}


public:
	Engine& engine;
	ResourceCache& cache;
	PokemonTrainer* player;
	PokemonTrainer* enemy;


	Battle(Battle&&) = delete;	//kopiowanie i przenoszenie wy³¹czone


	Battle(Engine& _engine,  ResourceCache& _resourceCache)
	: engine{_engine}
	, cache{_resourceCache}
	, player{}
	, enemy{}
	{}


	bool isStarting() const {
		return startingState != nullptr;
	}


	bool isStarted() const {
		return state != nullptr;
	}


	void start(PokemonTrainer* player,  PokemonTrainer* enemy) {
		this->player = player;
		this->enemy = enemy;

		preloadResources();
		startingState.reset(new BattleStarting{engine, cache});
	}


	void handleKeyboardEvents() {
		BattleState* newState = state->handleInput(*player, *enemy);
		if (newState == BattleState::battleEnd())
			state.reset(nullptr);
		else if (newState == BattleState::battleEscape())
		{
			engine.changeState(engine.state, 4);
			state.reset(nullptr);
		}
		else if (newState)
			state.reset(newState);
	}


	void updateStarting() {
		BattleState* newState = startingState->update(*player, *enemy);
		if (newState) {
			startingState.reset(nullptr);
			state.reset(newState);
		}
	}


	void update() {
		BattleState* newState = state->update(*player, *enemy);
		if (newState == BattleState::battleEnd())
			state.reset(nullptr);
		else if (newState == BattleState::battleEscape())
		{
			engine.changeState(engine.state, 4);
			state.reset(nullptr);
		}
		else if (newState)
			state.reset(newState);
	}
};