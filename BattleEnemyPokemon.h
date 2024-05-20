#pragma once


#include"BattleState.h"
#include"BattlePlayerPokemon.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattleEnemyPokemon : public BattleState {
	ALLEGRO_BITMAP* bottomBorder;
	ALLEGRO_BITMAP* topBorder;
	ALLEGRO_BITMAP* dust1;
	ALLEGRO_BITMAP* dust2;
	ALLEGRO_BITMAP* dust3;
	ALLEGRO_BITMAP* dust4;

	ALLEGRO_SAMPLE* pokeballPoof;
	ALLEGRO_SAMPLE* battle;
	ALLEGRO_SAMPLE_INSTANCE* battleInstance;

	float elapsedSeconds;


public:
	~BattleEnemyPokemon() noexcept override {
		al_destroy_sample(pokeballPoof);
		al_destroy_bitmap(dust4);
		al_destroy_bitmap(dust3);
		al_destroy_bitmap(dust2);
		al_destroy_bitmap(dust1);
		al_destroy_bitmap(topBorder);
		al_destroy_bitmap(bottomBorder);
	}


	BattleEnemyPokemon(ALLEGRO_SAMPLE* _battle,  ALLEGRO_SAMPLE_INSTANCE* _battleInstance)
	: bottomBorder{al_load_bitmap("battle/bottomBorder.png")}
	, topBorder{al_load_bitmap("battle/topBorder.png")}
	, dust1{al_load_bitmap("battle/dust1.png")}
	, dust2{al_load_bitmap("battle/dust2.png")}
	, dust3{al_load_bitmap("battle/dust3.png")}
	, dust4{al_load_bitmap("battle/dust4.png")}

	, pokeballPoof{al_load_sample("battle/pokeballPoof.mp3")}
	, battle{_battle}
	, battleInstance{_battleInstance}
	
	, elapsedSeconds{}
	{}


	BattleState* update(Engine& engine, PokemonTrainer& player, PokemonTrainer& enemy) override {
		float x = engine.getDispW()/2.0f - 420.0f;
		float y = engine.getDispH() - 170.0f;
		al_draw_bitmap(bottomBorder, x, y, 0);

		bool const ENEMY_MOVING = enemy.battleX < engine.getDispW();
		if (ENEMY_MOVING) {
			enemy.battleX += 400.0f * engine.getDeltaTime();
			enemy.battleImgDraw();
		} else {
			x = 40.0f;
			y = engine.getDispH() - 100.0f;
			al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), x, y, 0,
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
				al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), 50.0f+x, y-60.0f, 0,
					"%s", enemy.pokemons.front().name.c_str());
				al_draw_filled_rectangle(50.0f+x, y-45.0f, 50.0f+x+enemy.pokemons.front().hitPoints,
					y-40.0f,  al_map_rgb(0, 255, 0));
				al_draw_bitmap(topBorder, x, y-60.0f, 0);
				enemy.pokemons.front().battleImgDraw();
			} else 
				return new BattlePlayerPokemon(battle, battleInstance);
		}

		player.battleImgDraw();

		return nullptr;
	}
};