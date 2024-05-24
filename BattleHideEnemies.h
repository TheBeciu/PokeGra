#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"BattleState.h"
#include"BattleEnemyPokemon.h"
#include"BattlePlayerPokemon.h"
#include"BattlePlayerMove.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattleHideEnemies : public BattleState {
	Engine& engine;
	ResourceCache& cache;

	ALLEGRO_BITMAP* bottomBorder;


public:
	BattleHideEnemies(Engine& _engine, ResourceCache& _cache)
	: engine{_engine}
	, cache{_cache}

	, bottomBorder{cache.bitmap("battle/bottomBorder.png")}
	{}


	BattleState* update(PokemonTrainer& player, PokemonTrainer& enemy) override {
		float x = engine.getDispW() / 2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		bool const ENEMY_MOVING = enemy.battleX < engine.getDispW();
		if (ENEMY_MOVING)
			enemy.battleX += 400.0f * engine.getDeltaTime();
		enemy.battleY = 100.0f;
		enemy.battleImgDraw();

		bool const PLAYER_MOVING = -135.0f < player.battleX;
		if (PLAYER_MOVING)
			player.battleX -= 400.0f * engine.getDeltaTime();
		player.battleY = y - 130.0f;
		player.battleImgDraw();

		if (!ENEMY_MOVING && !PLAYER_MOVING)
			return new BattleEnemyPokemon(engine, cache,
				new BattlePlayerPokemon(engine, cache,
					new BattlePlayerMove(engine, cache)));

		return nullptr;
	}
};