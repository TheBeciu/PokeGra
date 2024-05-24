#pragma once


#include"Engine.h"
#include"ResourceCache.h"
#include"BattleState.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattleEnemyPokemon : public BattleState {
	Engine& engine;
	ResourceCache& cache;
	BattleState* nextState;

	ALLEGRO_BITMAP* bottomBorder;
	ALLEGRO_BITMAP* dust1;
	ALLEGRO_BITMAP* dust2;
	ALLEGRO_BITMAP* dust3;
	ALLEGRO_BITMAP* dust4;

	ALLEGRO_SAMPLE* pokeballPoof;

	ALLEGRO_FONT* font;

	float elapsedSeconds;


public:
	BattleEnemyPokemon(Engine& _engine,  ResourceCache& _cache,  BattleState* _nextState)
	: engine{_engine}
	, cache{_cache}
	, nextState{_nextState}

	, bottomBorder{cache.bitmap("battle/bottomBorder.png")}
	, dust1{cache.bitmap("battle/dust1.png")}
	, dust2{cache.bitmap("battle/dust2.png")}
	, dust3{cache.bitmap("battle/dust3.png")}
	, dust4{cache.bitmap("battle/dust4.png")}

	, pokeballPoof{cache.soundSample("battle/pokeballPoof.mp3")}
	
	, font{cache.font("battle/pokemon.ttf")}

	, elapsedSeconds{}
	{}


	BattleState* update(PokemonTrainer& player, PokemonTrainer& enemy) override {
		float x = engine.getDispW()/2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		x = 40.0f;
		y = engine.getDispH() - 100.0f;
		al_draw_textf(font, al_map_rgb(0, 0, 0), x, y, 0,
			"%s sent out %s!", enemy.name.c_str(), enemy.pokemons.front().name.c_str());
			
		if (elapsedSeconds == 0.0f)
			al_play_sample(pokeballPoof, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, nullptr);
		elapsedSeconds += engine.getDeltaTime();

		x = enemy.pokemons.front().battleX = engine.getDispW()-350.0f;
		y = enemy.pokemons.front().battleY = 100.0f;
		if (elapsedSeconds < 0.1f)
			al_draw_bitmap(dust1, x, y, 0);
		else if (elapsedSeconds < 0.2f)
			al_draw_bitmap(dust2, x, y, 0);
		else if (elapsedSeconds < 0.3f)
			al_draw_bitmap(dust3, x, y, 0);
		else if (elapsedSeconds < 0.4f)
			al_draw_bitmap(dust4, x, y, 0);
		else if (elapsedSeconds < 3.0f) {
			enemy.pokemons.front().battleNameDraw(cache);
			enemy.pokemons.front().battleStatsDraw(cache);
			enemy.pokemons.front().battleImgDraw();
		} else
			return nextState;

		return nullptr;
	}
};