#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"BattleState.h"
#include"BattleHideEnemies.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattleShowEnemies : public BattleState {
	Engine& engine;
	ResourceCache& cache;

	ALLEGRO_BITMAP* bottomBorder;

	ALLEGRO_FONT* font;

	float playerX;
	float enemyX;
	float elapsedSeconds;


public:
	BattleShowEnemies(Engine& _engine,  ResourceCache& _cache)
	: engine{_engine}
	, cache{_cache}

	, bottomBorder{cache.bitmap("battle/bottomBorder.png")}

	, font{cache.font("battle/pokemon.ttf")}

	, playerX{(float)engine.getDispW()}
	, enemyX{-135.0f}
	, elapsedSeconds{}
	{
		ALLEGRO_SAMPLE_INSTANCE* battleInstance = cache.soundSampleInstance("battle/battle.mp3");
		al_set_sample_instance_playmode(battleInstance, ALLEGRO_PLAYMODE_LOOP);
		al_play_sample_instance(battleInstance);
	}


	BattleState* update(PokemonTrainer& player, PokemonTrainer& enemy) override {
		float x = engine.getDispW()/2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		bool const ENEMY_MOVING = enemyX < engine.getDispW()-350.0f;
		if (ENEMY_MOVING)
			enemyX += 400.0f * engine.getDeltaTime();
		enemy.battleX = enemyX;
		enemy.battleY = 100.0f;
		enemy.battleImgDraw();

		bool const PLAYER_MOVING = 100.0f < playerX;
		if (PLAYER_MOVING)
			playerX -= 400.0f * engine.getDeltaTime();
		player.battleX = playerX;
		player.battleY = y - 130.0f;
		player.battleImgDraw();

		if (!ENEMY_MOVING && !PLAYER_MOVING) {
			player.battlePokeballsDraw(cache);
			enemy.battlePokeballsDraw(cache);

			x = 40.0f;
			y = engine.getDispH() - 100.0f;
			al_draw_textf(font, al_map_rgb(0, 0, 0), x, y, 0,
				"%s wants to battle!", enemy.name.c_str());

			elapsedSeconds += engine.getDeltaTime();
			if (4.0f <= elapsedSeconds)
				return new BattleHideEnemies(engine, cache);
		}

		return nullptr;
	}
};