#pragma once


#include"BattleState.h"
#include"BattleEnemyPokemon.h"

#include<allegro5/allegro_audio.h>
#include<allegro5/allegro.h>


class BattleFaceToFace : public BattleState {
	ALLEGRO_BITMAP* bottomBorder;
	ALLEGRO_BITMAP* smallPokeball;
	ALLEGRO_BITMAP* topBorder;
	ALLEGRO_SAMPLE* battle;
	ALLEGRO_SAMPLE_INSTANCE* battleInstance;
	float playerX;
	float enemyX;
	float elapsedSeconds;


public:
	~BattleFaceToFace() noexcept override {
		al_destroy_bitmap(topBorder);
		al_destroy_bitmap(smallPokeball);
		al_destroy_bitmap(bottomBorder);
	}


	BattleFaceToFace(Engine& engine,  ALLEGRO_SAMPLE* _battle, 
		ALLEGRO_SAMPLE_INSTANCE* _battleInstance)
	: bottomBorder{al_load_bitmap("battle/bottomBorder.png")}
	, smallPokeball{ al_load_bitmap("battle/smallPokeball.png") }
	, topBorder{ al_load_bitmap("battle/topBorder.png") }
	, battle{_battle}
	, battleInstance{_battleInstance}
	, playerX{(float)engine.getDispW()}
	, enemyX{-135.0f}
	, elapsedSeconds{}	//initialized to 0
	{
		al_set_sample_instance_playmode(battleInstance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(battleInstance, al_get_default_mixer());
		al_play_sample_instance(battleInstance);
	}


	BattleState* update(Engine& engine,  PokemonTrainer& player,  PokemonTrainer& enemy) override {
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
			al_draw_bitmap(topBorder, player.battleX, player.battleY - 60.0f, 0);
			for (std::size_t pokeball=0; pokeball<player.pokemons.size(); ++pokeball)
				al_draw_bitmap(smallPokeball,  25.0f*pokeball + player.battleX,
					player.battleY-60.0f,  0);

			al_draw_bitmap(topBorder, enemy.battleX, enemy.battleY-60.0f, 0);
			for (std::size_t pokeball=0; pokeball<enemy.pokemons.size(); ++pokeball)
				al_draw_bitmap(smallPokeball,  25.0f*pokeball + enemy.battleX,
					enemy.battleY-60.0f,  0);

			x = 40.0f;
			y = engine.getDispH() - 100.0f;
			al_draw_textf(engine.getFont(), al_map_rgb(0, 0, 0), x, y, 0,
				"%s wants to battle!", enemy.name.c_str());

			elapsedSeconds += engine.getDeltaTime();
			if (4.0f <= elapsedSeconds)
				return new BattleEnemyPokemon(battle, battleInstance);
		}

		return nullptr;
	}
};