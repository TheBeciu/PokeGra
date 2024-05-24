#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"BattleState.h"
#include"BattleEnemyPokemon.h"
#include"BattlePlayerPokemon.h"
#include"BattlePlayerMove.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattlePokemonDead : public BattleState {
	Engine& engine;
	ResourceCache& cache;

	ALLEGRO_BITMAP* bottomBorder;

	ALLEGRO_SAMPLE* deadSample;
	ALLEGRO_SAMPLE* winSample;
	ALLEGRO_SAMPLE* lostSample;
	ALLEGRO_SAMPLE* soundSample;

	ALLEGRO_FONT* font;

	bool enemyPokemonDead;

	float elapsedSeconds;


public:
	BattlePokemonDead(Engine& _engine,  ResourceCache& _cache,  bool _enemyPokemonDead)
	: engine{_engine}
	, cache{_cache}

	, bottomBorder{cache.bitmap("battle/bottomBorder.png")}

	, deadSample{cache.soundSample("battle/dead.mp3")}
	, winSample{cache.soundSample("battle/win.mp3")}
	, lostSample{cache.soundSample("battle/lost.mp3")}
	, soundSample{_enemyPokemonDead ? winSample : lostSample}

	, font{cache.font("battle/pokemon.ttf")}

	, elapsedSeconds{0}

	, enemyPokemonDead{_enemyPokemonDead}
	{}


	BattleState* update(PokemonTrainer& player, PokemonTrainer& enemy) override {
		float x = engine.getDispW() / 2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		if (elapsedSeconds == 0.0f)
			al_play_sample(deadSample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);

		if (enemyPokemonDead) {
			player.pokemons.front().battleNameDraw(cache);
			player.pokemons.front().battleStatsDraw(cache);
			player.pokemons.front().battleImgDraw();

			bool const ENEMY_MOVING = enemy.pokemons.front().battleX < engine.getDispW();
			if (ENEMY_MOVING)
				enemy.pokemons.front().battleX += 100.0f * engine.getDeltaTime();
			enemy.pokemons.front().battleY = 100.0f;
			enemy.pokemons.front().battleImgDraw();

			al_draw_textf(font, al_map_rgb(0, 0, 0), 40.0f, engine.getDispH() - 100.0f, 0,
				"%s is dead!", enemy.pokemons.front().name.c_str());

			if (enemy.pokemons.size() == 1 && elapsedSeconds == 0.0f) {
				cache.removeSoundSample("battle/battle.mp3");
				al_play_sample(winSample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);
			}
			if (enemy.pokemons.size() == 1)
				al_draw_textf(font, al_map_rgb(0, 0, 0), 40.0f, engine.getDispH() - 70.0f, 0,
					"%s has won!", player.name.c_str());

			if (!ENEMY_MOVING) {
				std::swap(enemy.pokemons.front(), enemy.pokemons.back());
				enemy.pokemons.pop_back();
				
				if (enemy.pokemons.size())
					return new BattleEnemyPokemon(engine, cache,
						new BattlePlayerMove(engine, cache));
				else {
					cache.removeSoundSample("battle/battle.mp3");
					enemy.hitPoints = 0.0f;
					return BattleState::battleEnd();
				}
			}
		} else {
			enemy.pokemons.front().battleNameDraw(cache);
			enemy.pokemons.front().battleStatsDraw(cache);
			enemy.pokemons.front().battleImgDraw();

			bool const PLAYER_MOVING = -135.0f < player.pokemons.front().battleX;
			if (PLAYER_MOVING)
				player.pokemons.front().battleX -= 50.0f * engine.getDeltaTime();
			player.pokemons.front().battleY = y - 130.0f;
			player.pokemons.front().battleImgDraw();
		
			al_draw_textf(font, al_map_rgb(0, 0, 0), 40.0f, engine.getDispH() - 100.0f, 0,
				"%s is dead!", player.pokemons.front().name.c_str());

			if (player.pokemons.size() == 1 && elapsedSeconds == 0.0f) {
				cache.removeSoundSample("battle/battle.mp3");
				al_play_sample(lostSample, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);
			}
			if (player.pokemons.size() == 1)
				al_draw_textf(font, al_map_rgb(0, 0, 0), 40.0f, engine.getDispH() - 70.0f, 0,
					"%s has won!", enemy.name.c_str());

			if (!PLAYER_MOVING) {
				std::swap(player.pokemons.front(), player.pokemons.back());
				player.pokemons.pop_back();

				if (player.pokemons.size())
					return new BattlePlayerPokemon(engine, cache,
						new BattlePokemonAttack(engine, cache, true));
				else {
					enemy.hitPoints = 0.0f;
					return BattleState::battleEnd();
				}
			}
		}

		elapsedSeconds += engine.getDeltaTime();

		return nullptr;
	}
};