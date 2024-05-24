#pragma once


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


	virtual BattleState* handleInput(PokemonTrainer& player,  PokemonTrainer& enemy) {
		return nullptr;
	}


	virtual BattleState* update(PokemonTrainer& player,  PokemonTrainer& enemy) {
		return nullptr;
	}
};