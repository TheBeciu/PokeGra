#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"BattleState.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattlePokemonAttack : public BattleState {
	Engine& engine;
	ResourceCache& cache;

	ALLEGRO_BITMAP* bottomBorder;

	ALLEGRO_FONT* font;

	float elapsedSeconds;

	bool enemyAttack;
	bool healing;

	int attackId;


public:
	BattlePokemonAttack(Engine& _engine,  ResourceCache& _cache,  bool _enemyAttack);


	BattleState* update(PokemonTrainer& _player,  PokemonTrainer& _enemy) override;
};