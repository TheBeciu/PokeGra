#pragma once


#include"BattleState.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattlePlayerAttack : public BattleState {
	ALLEGRO_BITMAP* bottomBorder;
	ALLEGRO_BITMAP* topBorder;

	PokemonAttack& pokemonAttack;
	ALLEGRO_SAMPLE* battle;
	ALLEGRO_SAMPLE_INSTANCE* battleInstance;
	ALLEGRO_SAMPLE* scratch;

	float elapsedSeconds;
	float damage;


public:
	~BattlePlayerAttack() noexcept override;


	BattlePlayerAttack(PokemonAttack& _pokemonAttack,  ALLEGRO_SAMPLE* _battle,
		ALLEGRO_SAMPLE_INSTANCE* _battleInstance);


	BattleState* update(Engine& engine,  PokemonTrainer& player,  PokemonTrainer& enemy) override;
};