#pragma once


#include"PokemonTrainer.h"
#include"Engine.h"
#include"BattleState.h"
#include"BattleStarting.h"

#include<memory>


class Battle {
	std::unique_ptr<BattleState> startingState;	//pocz¹tkowo zawiera nullptr
	std::unique_ptr<BattleState> state;			//pocz¹tkowo zawiera nullptr

public:
	Engine& engine;
	PokemonTrainer* player;
	PokemonTrainer* enemy;


	Battle(Battle&&) = delete;	//kopiowanie i przenoszenie wy³¹czone


	explicit Battle(Engine& _engine)
	: engine{_engine}
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

		//mo¿na usun¹æ alokacjê pamiêci, je¿eli wydajnoœæ jest niesatysfakcjonuj¹ca
		startingState.reset(new BattleStarting{});
	}


	void handleKeyboardEvents() {
		BattleState* newState = state->handleInput(engine, *player, *enemy);
		if (newState == BattleState::battleEnd())
			state.reset(nullptr);
		else if (newState)
			state.reset(newState);
	}


	void updateStarting() {
		BattleState* newState = startingState->update(engine, *player, *enemy);
		if (newState) {
			startingState.reset(nullptr);
			state.reset(newState);
		}
	}


	void update() {
		BattleState* newState = state->update(engine, *player, *enemy);
		if (newState == BattleState::battleEnd())
			state.reset(nullptr);
		else if (newState)
			state.reset(newState);
	}
};