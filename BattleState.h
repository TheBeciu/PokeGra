#pragma once


#include"Engine.h"
#include"PokemonTrainer.h"


class BattleState {
public:
	static BattleState* battleEnd() {
		//Zwraca wska�nik na obiekt, kt�ry oznacza koniec walki

		static BattleState battleEnd;
		return &battleEnd;
	}


	BattleState(BattleState&&) = delete;	//kopiowanie i przenoszenie wy��czone


	virtual ~BattleState() noexcept
	{}


	BattleState()
	{}


	virtual BattleState* handleInput(Engine& engine,  PokemonTrainer& player,
			PokemonTrainer& enemy) {
		return nullptr;
	}


	virtual BattleState* update(Engine& engine,  PokemonTrainer& player,  PokemonTrainer& enemy) {
		return nullptr;
	}
};